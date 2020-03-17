#pragma once
#include <nn/hac/define/types.h>
#include <nn/hac/define/macro.h>

namespace nn
{
namespace hac
{
	namespace hierarchicalintegrity
	{
		static const uint32_t kStructMagic = _MAKE_STRUCT_MAGIC_U32("IVFC");
		static const size_t kDefaultLayerNumForRomFs = 6;
		static const size_t kHeaderAlignLen = 0x20;
		static const size_t kSaltSourceLen = 0x20;
		static const size_t kHacRomfsMasterHashLen = 0x20;

		enum class TypeId
		{
			CTR_RomFs = 0x10000, // Nintendo 3DS
			HAC_RomFs = 0x20000 // Nintendo Switch
		};
	}
	
#pragma pack(push,1)
	struct sHierarchicalIntegrityHeader
	{
		le_uint32_t st_magic;
		le_uint32_t type_id;
		le_uint32_t master_hash_size;
		le_uint32_t layer_num;
	};
	static_assert(sizeof(sHierarchicalIntegrityHeader) == 0x10, "sHierarchicalIntegrityHeader size.");

	struct sHierarchicalIntegrityLayerInfo
	{
		le_uint64_t offset;
		le_uint64_t size;
		le_uint32_t block_size;
		byte_t reserved[4];
	};
	static_assert(sizeof(sHierarchicalIntegrityLayerInfo) == 0x18, "sHierarchicalIntegrityLayerInfo size.");

	struct sHierarchicalIntegrityForHacRomfs
	{
		sHierarchicalIntegrityHeader header;
		sHierarchicalIntegrityLayerInfo layer[hierarchicalintegrity::kDefaultLayerNumForRomFs];
		byte_t salt_source[hierarchicalintegrity::kSaltSourceLen];
		byte_t master_hash[hierarchicalintegrity::kHacRomfsMasterHashLen];
	};
	static_assert(sizeof(sHierarchicalIntegrityForHacRomfs) == 0xE0, "sHierarchicalIntegrityForHacRomfs size.");
#pragma pack(pop)
}
}