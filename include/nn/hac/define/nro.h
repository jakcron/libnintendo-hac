#pragma once
#include <nn/hac/define/types.h>
#include <nn/hac/define/macro.h>

namespace nn
{
namespace hac
{
	namespace nro
	{
		static const uint32_t kNroStructMagic = _MAKE_STRUCT_MAGIC_U32("NRO0");
		static const uint32_t kDefaultFormatVersion = 0;
		static const size_t kRoCrtSize = 8;
		static const size_t kModuleIdSize = 32;
	}

#pragma pack(push,1)

	struct sNroHeader
	{
		struct sRoCrt
		{
			le_uint32_t entry_point_insn;
			le_uint32_t mod_offset;
		};

		struct sSection
		{
			le_uint32_t memory_offset;
			le_uint32_t size;
		};

		sRoCrt ro_crt;
		byte_t reserved_0[8];
		le_uint32_t st_magic;
		le_uint32_t format_version;
		le_uint32_t size;
		le_uint32_t flags;
		sSection text;
		sSection ro;
		sSection data;
		le_uint32_t bss_size;
		byte_t reserved_1[4];
		byte_t module_id[nro::kModuleIdSize];
		byte_t reserved_2[8];
		sSection embedded;
		sSection dyn_str;
		sSection dyn_sym;
	};
	static_assert(sizeof(sNroHeader) == 0x80, "sNroHeader size.");

#pragma pack(pop)
}
}