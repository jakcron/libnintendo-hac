#pragma once
#include <nn/hac/define/types.h>
#include <nn/hac/define/bktr.h>

namespace nn
{
namespace hac
{
	namespace nca
	{
		static const uint32_t kNca2StructMagic = tc::bn::make_struct_magic_uint32("NCA2");
		static const uint32_t kNca3StructMagic = tc::bn::make_struct_magic_uint32("NCA3");
		static const size_t kSectorSize = 0x200;
		static const size_t kPartitionNum = 4;
		static const size_t kHeaderSectorNum = 6;
		static const size_t kHeaderSize = kSectorSize * kHeaderSectorNum;
		static const size_t kRightsIdLen = 0x10;
		static const size_t kKeyAreaSize = 0x100;
		static const size_t kKeyAreaKeyNum = kKeyAreaSize / sizeof(detail::aes128_key_t);
		static const size_t kKeyAreaEncryptionKeyNum = 3;
		static const size_t kHashInfoLen = 0xF8;
		static const size_t kPatchInfoLen = 0x40;
		static const size_t kSparseInfoLen = 0x30;
		static const uint16_t kDefaultFsHeaderVersion = 2;

		using key_area_t = std::array<detail::aes128_key_t, kKeyAreaKeyNum>;

		enum HeaderFormatVersion
		{
			FORMAT_NCA2 = 2,
			FORMAT_NCA3 = 3
		};

		enum ProgramContentPartitionIndex
		{
			PARTITION_CODE = 0,
			PARTITION_DATA = 1,
			PARTITION_LOGO = 2,
		};

		enum class DistributionType : byte_t
		{
			Download,
			GameCard
		};

		enum class ContentType : byte_t
		{
			Program,
			Meta,
			Control,
			Manual,
			Data,
			PublicData
		};

		enum KeyBankIndex
		{
			KEY_AESXTS_0,
			KEY_AESXTS_1,
			KEY_AESCTR,
			KEY_UNUSED_3,
			KEY_AESCTR_HW
		};

		enum KeyAreaEncryptionKeyIndex
		{
			KAEK_IDX_APPLICATION,
			KAEK_IDX_OCEAN,
			KAEK_IDX_SYSTEM
		};

		enum class FormatType : byte_t
		{
			RomFs,
			PartitionFs
		};

		enum class HashType : byte_t
		{
			Auto,
			None,
			HierarchicalSha256,
			HierarchicalIntegrity // IVFC
		};

		enum class EncryptionType : byte_t 
		{
			Auto,
			None,
			AesXts,
			AesCtr,
			AesCtrEx
		};
	}
	
#pragma pack(push,1)
	struct sContentArchiveHeader
	{
		tc::bn::le32<uint32_t> st_magic;
		byte_t distribution_type;
		byte_t content_type;
		byte_t key_generation;
		byte_t key_area_encryption_key_index;
		tc::bn::le64<uint64_t> content_size;
		tc::bn::le64<uint64_t> program_id;
		tc::bn::le32<uint32_t> content_index;
		tc::bn::le32<uint32_t> sdk_addon_version;
		byte_t key_generation_2;
		byte_t signature_key_generation;
		std::array<byte_t, 0xE> reserved_2;
		detail::rights_id_t rights_id;
		struct sPartitionEntry
		{
			tc::bn::le32<uint32_t> start_blk; // block units
			tc::bn::le32<uint32_t> end_blk; // block units
			byte_t enabled;
			std::array<byte_t, 0x7> reserved;
		};
		std::array<sPartitionEntry, nca::kPartitionNum> partition_entry;
		std::array<detail::sha256_hash_t, nca::kPartitionNum> fs_header_hash;
		nca::key_area_t key_area;
	};
	static_assert(sizeof(sContentArchiveHeader) == 0x200, "sContentArchiveHeader size.");

	struct sContentArchiveBucketInfo
	{
		tc::bn::le64<uint64_t> offset;
		tc::bn::le64<uint64_t> size;
		sBucketTreeHeader header;
	};
	static_assert(sizeof(sContentArchiveBucketInfo) == 0x20, "sContentArchiveBucketInfo size.");

	struct sContentArchiveFsHeaderSparseInfo
	{
		// if sparse info generation is non-zero then a sparse layer exists
		sContentArchiveBucketInfo bucket;
		tc::bn::le64<uint64_t> physical_offset;
		tc::bn::le16<uint16_t> generation;
		std::array<byte_t, 0x6> reserved_0;
	};
	static_assert(sizeof(sContentArchiveFsHeaderSparseInfo) == nca::kSparseInfoLen, "sContentArchiveFsHeaderSparseInfo size.");

	struct sContentArchiveFsHeader
	{
		// 0x00
		tc::bn::le16<uint16_t> version;
		// 0x02
		byte_t format_type;
		// 0x03
		byte_t hash_type;
		// 0x04
		byte_t encryption_type;
		// 0x5
		std::array<byte_t, 0x3> reserved_0;
		// 0x8
		std::array<byte_t, nca::kHashInfoLen> hash_info; // size=0xf8
		// 0x100
		std::array<byte_t, nca::kPatchInfoLen> patch_info; // size=0x40
		// 0x140
		tc::bn::le32<uint32_t> generation;
		// 0x144
		tc::bn::le32<uint32_t> secure_value;
		// 0x148
		sContentArchiveFsHeaderSparseInfo sparse_info;
		//std::array<byte_t, nca::kSparseInfoLen>  sparse_info; // size=0x30
		// 0x178
		std::array<byte_t, 0x88> reserved_1;
		// 0x200
	};
	static_assert(sizeof(sContentArchiveFsHeader) == 0x200, "sContentArchiveFsHeader size.");

	struct sContentArchiveHeaderBlock
	{
		detail::rsa2048_signature_t signature_main;
		detail::rsa2048_signature_t signature_acid;
		sContentArchiveHeader header;
		std::array<sContentArchiveFsHeader, nn::hac::nca::kPartitionNum> fs_header;
	};
	static_assert(sizeof(sContentArchiveHeaderBlock) == 0xC00, "sContentArchiveHeaderBlock size.");

#pragma pack(pop)
}
}