#pragma once
#include <nn/hac/define/nca.h>
#include <string>

namespace nn
{
namespace hac
{
	class ContentArchiveUtil
	{
	public:
		static inline size_t sectorToOffset(size_t sector_index) { return sector_index * nn::hac::nca::kSectorSize; }
		static void decryptContentArchiveHeader(const byte_t* src, byte_t* dst, const fnd::aes::sAesXts128Key& key);
		static byte_t getMasterKeyRevisionFromKeyGeneration(byte_t key_generation);
		static void getNcaPartitionAesCtr(const nn::hac::sNcaFsHeader* hdr, byte_t* ctr);

		static std::string getFormatVersionAsString(nn::hac::nca::HeaderFormatVersion val);
		static std::string getProgramContentParititionIndexAsString(nn::hac::nca::ProgramContentPartitionIndex val);
		static std::string getDistributionTypeAsString(nn::hac::nca::DistributionType val);
		static std::string getContentTypeAsString(nn::hac::nca::ContentType val);
		static std::string getFormatTypeAsString(nn::hac::nca::FormatType val);
		static std::string getHashTypeAsString(nn::hac::nca::HashType val);
		static std::string getEncryptionTypeAsString(nn::hac::nca::EncryptionType val);
		static std::string getKeyAreaEncryptionKeyIndexAsString(nn::hac::nca::KeyAreaEncryptionKeyIndex val);

	private:
		const std::string kModuleName = "CONTENT_ARCHIVE_UTIL";
	};
}
}