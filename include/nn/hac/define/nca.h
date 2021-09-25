#pragma once
#include <nn/hac/define/types.h>
#include <fnd/aes.h>
#include <fnd/sha.h>
#include <fnd/rsa.h>
#include <nn/hac/define/macro.h>
#include <nn/hac/define/bktr.h>

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
		static const size_t kHashInfoLen = 0xF8;
		static const size_t kPatchInfoLen = 0x40;
		static const size_t kSparseInfoLen = 0x30;
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

	struct sContentArchiveBucketInfo
	{
		static const size_t kHeaderSize = 0x10;
		le_uint64_t offset;
		le_uint64_t size;
		sBucketTreeHeader header;
	};
	static_assert(sizeof(sContentArchiveBucketInfo) == 0x20, "sContentArchiveBucketInfo size.");

	struct sContentArchiveFsHeaderSparseInfo
	{
		// if sparse info generation is non-zero then a sparse layer exists
		sContentArchiveBucketInfo bucket;
		le_uint64_t physical_offset;
		le_uint16_t generation;
		byte_t reserved_0[6];
	};
	static_assert(sizeof(sContentArchiveFsHeaderSparseInfo) == nca::kSparseInfoLen, "sContentArchiveFsHeaderSparseInfo size.");

	struct sContentArchiveFsHeader
	{
		// 0x00
		le_uint16_t version;
		// 0x02
		byte_t format_type;
		// 0x03
		byte_t hash_type;
		// 0x04
		byte_t encryption_type;
		// 0x5
		byte_t reserved_0[3];
		// 0x8
		byte_t hash_info[nca::kHashInfoLen]; // size=0xf8
		// 0x100
		byte_t patch_info[nca::kPatchInfoLen]; // size=0x40
		// 0x140
		le_uint32_t generation;
		// 0x144
		le_uint32_t secure_value;
		// 0x148
		sContentArchiveFsHeaderSparseInfo sparse_info;
		//byte_t sparse_info[nca::kSparseInfoLen]; // size=0x30
		// 0x178
		byte_t reserved_1[0x88];
		// 0x200
	};
	static_assert(sizeof(sContentArchiveFsHeader) == 0x200, "sContentArchiveFsHeader size.");

	struct sContentArchiveHeaderBlock
	{
		byte_t signature_main[fnd::rsa::kRsa2048Size];
		byte_t signature_acid[fnd::rsa::kRsa2048Size];
		sContentArchiveHeader header;
		sContentArchiveFsHeader fs_header[nn::hac::nca::kPartitionNum];
	};
	static_assert(sizeof(sContentArchiveHeaderBlock) == 0xC00, "sContentArchiveHeaderBlock size.");

#pragma pack(pop)
}
}