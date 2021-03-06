#pragma once
#include <nn/hac/define/types.h>
#include <fnd/sha.h>
#include <nn/hac/define/macro.h>

namespace nn
{
namespace hac
{
	namespace ini
	{
		static const uint32_t kIniStructMagic = _MAKE_STRUCT_MAGIC_U32("INI1");
		static const size_t kMaxKipNum = 0x50;
	}
	
#pragma pack(push,1)
	struct sIniHeader
	{
		le_uint32_t st_magic;
		le_uint32_t size;
		le_uint32_t kip_num;
		byte_t reserved_01[0x4];
	};
	static_assert(sizeof(sIniHeader) == 0x10, "sIniHeader size.");
#pragma pack(pop)
}
}