#pragma once
#include <nn/hac/define/nca.h>

namespace nn
{
namespace hac
{
	class ContentArchiveHeader
	{
	public:
		struct sPartitionEntry
		{
			byte_t header_index;
			uint64_t offset;
			uint64_t size;
			detail::sha256_hash_t fs_header_hash;

			const sPartitionEntry& operator=(const sPartitionEntry& other)
			{
				header_index = other.header_index;
				offset = other.offset;
				size = other.size;
				fs_header_hash = other.fs_header_hash;

				return *this;
			}

			bool operator==(const sPartitionEntry& other) const
			{
				return (header_index == other.header_index) \
					&& (offset == other.offset) \
					&& (size == other.size) \
					&& (fs_header_hash == other.fs_header_hash);
			}

			bool operator!=(const sPartitionEntry& other) const
			{
				return !operator==(other);
			}
		};

		ContentArchiveHeader();
		ContentArchiveHeader(const ContentArchiveHeader& other);

		void operator=(const ContentArchiveHeader& other);
		bool operator==(const ContentArchiveHeader& other) const;
		bool operator!=(const ContentArchiveHeader& other) const;

		// IByteModel
		void toBytes();
		void fromBytes(const byte_t* bytes, size_t len);
		const tc::ByteData& getBytes() const;

		// variables
		void clear();

		byte_t getFormatVersion() const;
		void setFormatVersion(byte_t ver);
		
		nca::DistributionType getDistributionType() const;
		void setDistributionType(nca::DistributionType type);
		
		nca::ContentType getContentType() const;
		void setContentType(nca::ContentType type);
		
		byte_t getKeyGeneration() const;
		void setKeyGeneration(byte_t gen);

		byte_t getSignatureKeyGeneration() const;
		void setSignatureKeyGeneration(byte_t gen);
		
		byte_t getKeyAreaEncryptionKeyIndex() const;
		void setKeyAreaEncryptionKeyIndex(byte_t index);
		
		uint64_t getContentSize() const;
		void setContentSize(uint64_t size);
		
		uint64_t getProgramId() const;
		void setProgramId(uint64_t program_id);
		
		uint32_t getContentIndex() const;
		void setContentIndex(uint32_t index);
		
		uint32_t getSdkAddonVersion() const;
		void setSdkAddonVersion(uint32_t version);
		
		bool hasRightsId() const;
		const nn::hac::detail::rights_id_t& getRightsId() const;
		void setRightsId(const nn::hac::detail::rights_id_t& rights_id);

		const std::vector<sPartitionEntry>& getPartitionEntryList() const;
		void setPartitionEntryList(const std::vector<sPartitionEntry>& partition_entry_list);
		
		const byte_t* getKeyArea() const;
		void setKeyArea(const byte_t* key_area);

	private:
		const std::string kModuleName = "CONTENT_ARCHIVE_HEADER";

		// binary
		tc::ByteData mRawBinary;

		// data
		byte_t mFormatVersion;
		nca::DistributionType mDistributionType;
		nca::ContentType mContentType;
		byte_t mKeyGeneration;
		byte_t mSignatureKeyGeneration;
		byte_t mKaekIndex;
		uint64_t mContentSize;
		uint64_t mProgramId;
		uint32_t mContentIndex;
		uint32_t mSdkAddonVersion;
		nn::hac::detail::rights_id_t mRightsId;
		std::vector<sPartitionEntry> mPartitionEntryList;
		tc::ByteData mKeyArea;

		uint64_t blockNumToSize(uint32_t block_num) const;
		uint32_t sizeToBlockNum(uint64_t real_size) const;
	};
}
}