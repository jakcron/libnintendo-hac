#include <nn/hac/PartitionFsSnapshotGenerator.h>
#include <tc/io/SubStream.h>
#include <tc/io/IOUtil.h>
#include <tc/crypto/Sha256Generator.h>
#include <tc/crypto/CryptoException.h>

#include <nn/hac/define/pfs.h>

#include <fmt/core.h>
#include <tc/cli/FormatUtil.h>

nn::hac::PartitionFsSnapshotGenerator::PartitionFsSnapshotGenerator(const std::shared_ptr<tc::io::IStream>& stream, ValidationMode validate_mode) :
	FileSystemSnapshot()
{
	// validate stream properties
	if (stream == nullptr)
	{
		throw tc::ObjectDisposedException("nn::hac::PartitionFsSnapshotGenerator", "Failed to open input stream.");
	}
	if (stream->canRead() == false || stream->canSeek() == false)
	{
		throw tc::NotSupportedException("nn::hac::PartitionFsSnapshotGenerator", "Input stream requires read/seek permissions.");
	}

	// validate and read base PartitionFs header
	nn::hac::sPfsHeader hdr;
	if (stream->length() < tc::io::IOUtil::castSizeToInt64(sizeof(nn::hac::sPfsHeader)))
	{
		throw tc::ArgumentOutOfRangeException("nn::hac::PartitionFsSnapshotGenerator", "Input stream is too small.");
	}
	stream->seek(0, tc::io::SeekOrigin::Begin);
	stream->read((byte_t*)(&hdr), sizeof(nn::hac::sPfsHeader));

	// parse base header
	enum FsType
	{
		TYPE_PFS0,
		TYPE_HFS0
	} fs_type;
	size_t file_entry_size = 0;
	switch(hdr.st_magic.unwrap())
	{
		case (pfs::kPfsStructMagic):
			fs_type = TYPE_PFS0;
			file_entry_size = sizeof(sPfsFile);
			break;
		case (pfs::kHashedPfsStructMagic):
			fs_type = TYPE_HFS0;
			file_entry_size = sizeof(sHashedPfsFile);
			break;	
		default:
			throw tc::ArgumentOutOfRangeException("nn::hac::PartitionFsSnapshotGenerator", "sPfsHeader header is corrupt (Bad struct magic).");
	}

	// determine complete header size
	size_t pfs_full_header_size = sizeof(sPfsHeader) + file_entry_size * hdr.file_num.unwrap() + hdr.name_table_size.unwrap();
	if (stream->length() < tc::io::IOUtil::castSizeToInt64(pfs_full_header_size))
	{
		throw tc::ArgumentOutOfRangeException("nn::hac::PartitionFsSnapshotGenerator", "Input stream is too small.");
	}

	// read raw file entry table data
	tc::ByteData file_entry_table_raw = tc::ByteData(file_entry_size * hdr.file_num.unwrap());
	stream->read(file_entry_table_raw.data(), file_entry_table_raw.size());

	// read raw name string table
	tc::ByteData name_table_raw = tc::ByteData(hdr.name_table_size.unwrap());
	stream->read(name_table_raw.data(), name_table_raw.size());


	// parse header sections
	struct SectionInformation
	{
		std::string name;
		int64_t offset;
		int64_t size;
		size_t hashed_size;
		std::array<byte_t, 32> hash;
	};
	
	std::vector<SectionInformation> section;

	int64_t pos = 0;
	for (size_t i = 0, file_num = hdr.file_num.unwrap(); i < file_num; i++)
	{
		SectionInformation tmp;

		if (fs_type == TYPE_PFS0)
		{
			nn::hac::sPfsFile& file_entry = ((nn::hac::sPfsFile*)file_entry_table_raw.data())[i];

			if (file_entry.data_offset.unwrap() != pos)
			{
				throw tc::ArgumentOutOfRangeException("nn::hac::PartitionFsSnapshotGenerator", "sPfsFile entry had unexpected data offset.");
			}

			tmp.name = std::string((char*)name_table_raw.data() + file_entry.name_offset.unwrap());
			tmp.offset = file_entry.data_offset.unwrap() + tc::io::IOUtil::castSizeToInt64(pfs_full_header_size);
			tmp.size = file_entry.size.unwrap();
			tmp.hashed_size = 0;
			memset(tmp.hash.data(), 0, tmp.hash.size());

			pos += file_entry.size.unwrap();
		}
		else if (fs_type == TYPE_HFS0)
		{
			nn::hac::sHashedPfsFile& file_entry = ((nn::hac::sHashedPfsFile*)file_entry_table_raw.data())[i];

			// HFS partitions do not strictly follow each other as the secure partition offset also has to lie on the beginning of a page.
			//if (file_entry.data_offset.unwrap() != pos)
			//{
			//	throw tc::ArgumentOutOfRangeException("nn::hac::PartitionFsSnapshotGenerator", "sHashedPfsFile entry had unexpected data offset.");
			//}

			tmp.name = std::string((char*)name_table_raw.data() + file_entry.name_offset.unwrap());
			tmp.offset = file_entry.data_offset.unwrap() + tc::io::IOUtil::castSizeToInt64(pfs_full_header_size);
			tmp.size = file_entry.size.unwrap();
			tmp.hashed_size = file_entry.hash_protected_size.unwrap();
			memcpy(tmp.hash.data(), file_entry.hash.data(), tmp.hash.size());

			pos += file_entry.size.unwrap();
		}

		section.push_back(tmp);
	}

	// Add root directory
	dir_entries.push_back(DirEntry());
	auto cur_dir = &dir_entries.front();
	cur_dir->dir_listing.abs_path = tc::io::Path("/");
	dir_entry_path_map[tc::io::Path("/")] = dir_entries.size()-1;

	// populate virtual filesystem
	std::array<byte_t, tc::crypto::Sha256Generator::kHashSize> hash_tmp;
	for (size_t i = 0; i < section.size(); i++)
	{
		if (section[i].size != 0)
		{			
			FileEntry tmp;
			
			// if we verify the hashes, we import the hashable part first and verify
			if ((validate_mode == ValidationMode_Warn || validate_mode == ValidationMode_Throw)  && section[i].hashed_size != 0)
			{	
				auto tmp_data = tc::ByteData(section[i].hashed_size);
				stream->seek(section[i].offset, tc::io::SeekOrigin::Begin);
				stream->read(tmp_data.data(), tmp_data.size());

				tc::crypto::GenerateSha256Hash(hash_tmp.data(), tmp_data.data(), tmp_data.size());
				if (memcmp(hash_tmp.data(), section[i].hash.data(), hash_tmp.size()) != 0)
				{
					std::string error_msg = fmt::format("\"{:s}\" failed hash check.", section[i].name);
					if (validate_mode == ValidationMode_Throw)
					{
						throw tc::crypto::CryptoException("nn::hac::PartitionFsSnapshotGenerator", error_msg);
					}
					else if (validate_mode == ValidationMode_Warn)
					{
						fmt::print("[WARNING] {:s}\n", error_msg);
					}
				}
			}
			
			try {
				tmp.stream = std::make_shared<tc::io::SubStream>(tc::io::SubStream(stream, section[i].offset, section[i].size));
			} catch (tc::Exception& e) {
				fmt::print("[WARNING] Failed to add file \"{:s}\". ({:s})\n", section[i].name, e.error());
			}
			
			

			// create file path
			tc::io::Path file_path = cur_dir->dir_listing.abs_path + section[i].name;

			// add file entry to list
			file_entries.push_back(std::move(tmp));

			// add file entry to map
			file_entry_path_map[file_path] = file_entries.size()-1;

			// add name to parent directory listing
			cur_dir->dir_listing.file_list.push_back(section[i].name);
		}
	}
}