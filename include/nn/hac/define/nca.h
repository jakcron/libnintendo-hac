#pragma once
#include <nn/hac/define/types.h>
#include <fnd/aes.h>
#include <fnd/sha.h>
#include <fnd/rsa.h>
#include <nn/hac/define/macro.h>

namespace nn
{
namespace hac
{
	namespace nca
	{
		static const uint32_t kNca2StructMagic = _MAKE_STRUCT_MAGIC_U32("NCA2");
		static const uint32_t kNca3StructMagic = _MAKE_STRUCT_MAGIC_U32("NCA3");
		static const size_t kSectorSize = 0x200;
		static const size_t kPartitionNum = 4;
		static const size_t kHeaderSectorNum = 6;
		static const size_t kHeaderSize = kSectorSize * kHeaderSectorNum;
		static const size_t kRightsIdLen = 0x10;
		static const size_t kKeyAreaSize = 0x100;
		static const size_t kKeyAreaKeyNum = kKeyAreaSize / fnd::aes::kAes128KeySize;
		static const size_t kKeyAreaEncryptionKeyNum = 3;
		static const size_t kFsHeaderHashSuperblockLen = 0x138;
		static const uint16_t kDefaultFsHeaderVersion = 2;

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
		le_uint32_t st_magic;
		byte_t distribution_type;
		byte_t content_type;
		byte_t key_generation;
		byte_t key_area_encryption_key_index;
		le_uint64_t content_size;
		le_uint64_t program_id;
		le_uint32_t content_index;
		le_uint32_t sdk_addon_version;
		byte_t key_generation_2;
		byte_t signature_key_generation;
		byte_t reserved_2[0xe];
		byte_t rights_id[nca::kRightsIdLen];
		struct sPartitionEntry
		{
			le_uint32_t start_blk; // block units
			le_uint32_t end_blk; // block units
			byte_t enabled;
			byte_t reserved[7];
		} partition_entry[nca::kPartitionNum];
		fnd::sha::sSha256Hash fs_header_hash[nca::kPartitionNum];
		byte_t key_area[nca::kKeyAreaSize];
	};
	static_assert(sizeof(sContentArchiveHeader) == 0x200, "sContentArchiveHeader size.");

	struct sNcaFsHeader
	{
		le_uint16_t version;
		byte_t format_type;
		byte_t hash_type;
		byte_t encryption_type;
		byte_t reserved_0[3];
		byte_t hash_superblock[nca::kFsHeaderHashSuperblockLen];
		le_uint32_t generation;
		le_uint32_t secure_value;
		byte_t reserved_1[0xB8];
	};
	static_assert(sizeof(sNcaFsHeader) == 0x200, "sNcaFsHeader size.");

	struct sContentArchiveHeaderBlock
	{
		byte_t signature_main[fnd::rsa::kRsa2048Size];
		byte_t signature_acid[fnd::rsa::kRsa2048Size];
		sContentArchiveHeader header;
		sNcaFsHeader fs_header[nn::hac::nca::kPartitionNum];
	};
	static_assert(sizeof(sContentArchiveHeaderBlock) == 0xC00, "sContentArchiveHeaderBlock size.");

#pragma pack(pop)
}
}