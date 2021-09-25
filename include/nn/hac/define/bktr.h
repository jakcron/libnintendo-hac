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
	namespace bktr
	{
		static const uint32_t kBktrStructMagic = _MAKE_STRUCT_MAGIC_U32("BKTR");
		static const uint32_t kBktrVersion = 1;

		static const size_t kNodeSizeMin = 0x400; // 1KB
		static const size_t kNodeSizeMax = 0x80000; // 512KB
	}

#pragma pack(push,1)
	struct sBucketTreeHeader
	{	
		le_uint32_t st_magic; // BKTR
		le_uint32_t version; // s32
		le_uint32_t entry_count; // s32
		byte_t reserved_0[4];
	};
	static_assert(sizeof(sBucketTreeHeader) == 0x10, "sBucketTreeHeader size.");

	struct sBucketTreeNodeHeader
	{
		le_uint32_t index; // s32
		le_uint32_t count; // s32
		le_uint64_t offset; // s64
	};
	static_assert(sizeof(sBucketTreeNodeHeader) == 0x10, "sBucketTreeNodeHeader size.");

	struct sBucketTreeEntrySetHeader
	{
		le_uint32_t index; // s32
		le_uint32_t count; // s32
		le_uint64_t offset; // s64
		le_uint64_t size; // s64
	};
	static_assert(sizeof(sBucketTreeEntrySetHeader) == 0x18, "sBucketTreeEntrySetHeader size.");
#pragma pack(pop)
}
}