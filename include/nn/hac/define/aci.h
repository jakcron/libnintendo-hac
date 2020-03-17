#pragma once
#include <nn/hac/define/types.h>
#include <fnd/rsa.h>
#include <nn/hac/define/macro.h>

namespace nn
{
namespace hac
{
	namespace aci
	{
		static const uint32_t kAciStructMagic = _MAKE_STRUCT_MAGIC_U32("ACI0");
		static const uint32_t kAciDescStructMagic = _MAKE_STRUCT_MAGIC_U32("ACID");
		static const size_t kSectionAlignSize = 0x10;

		enum class MemoryRegion : byte_t
		{
			Application,
			Applet,
			SecureSystem,
			NonSecureSystem
		};
	}
#pragma pack(push,1)
	struct sAciSection
	{
		le_uint32_t offset;
		le_uint32_t size;
	};
	static_assert(sizeof(sAciSection) == 0x8, "sAciSection size"); 

	struct sAciHeader
	{
		le_uint32_t st_magic;
		byte_t reserved_00[0xC];
		le_uint64_t program_id;
		byte_t reserved_01[0x8];
		sAciSection fac;
		sAciSection sac;
		sAciSection kc;
	};
	static_assert(sizeof(sAciHeader) == 0x38, "sAciHeader size"); 

	union sAciDescHeaderFlag
	{
		struct 
		{
			uint32_t production : 1;
			uint32_t unqualified_approval : 1;
			uint32_t memory_region : 2; // added in FW 5.0.0 / kernel version 9.1.0??
			uint32_t :0; 
		};
		uint32_t raw;
	};
	static_assert(sizeof(sAciDescHeaderFlag) == 0x4, "sAciDescHeaderFlag size"); 

	struct sAciDescHeader
	{
		byte_t signature[fnd::rsa::kRsa2048Size];
		byte_t nca_rsa_signature2_modulus[fnd::rsa::kRsa2048Size];
		le_uint32_t st_magic;
		le_uint32_t signed_size;
		byte_t reserved_00[0x4];
		le_uint32_t flags;
		le_uint64_t program_id_min;
		le_uint64_t program_id_max;
		sAciSection fac;
		sAciSection sac;
		sAciSection kc;
	};
	static_assert(sizeof(sAciDescHeader) == 0x238, "sAciDescHeader size"); 
#pragma pack(pop)
}
}