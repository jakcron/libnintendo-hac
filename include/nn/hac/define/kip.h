#pragma once
#include <nn/hac/define/types.h>
#include <fnd/sha.h>
#include <nn/hac/define/macro.h>

namespace nn
{
namespace hac
{
	namespace kip
	{
		static const uint32_t kKipStructMagic = _MAKE_STRUCT_MAGIC_U32("KIP1");
		static const uint32_t kDefaultKipVersion = 1;
		static const size_t kNameMaxLen = 0xC;
		static const size_t kKernCapabilityNum = 0x20;
		static const size_t kKernCapabilitySize = kKernCapabilityNum * sizeof(uint32_t);
	}
	
#pragma pack(push,1)
	
	struct sKipHeader
	{
		// sub struct definitions
		struct sFlag 
		{
			byte_t text_compress : 1;
			byte_t ro_compress : 1;
			byte_t data_compress : 1;
			byte_t is_64bit_instruction : 1;
			byte_t is_64bit_address_space : 1;
			byte_t use_secure_memory : 1;
			byte_t :0;
		};
		struct sCodeSegment
		{
			le_uint32_t memory_offset;
			le_uint32_t memory_size;
			le_uint32_t file_size;
		};

		// layout
		le_uint32_t st_magic;
		char name[kip::kNameMaxLen];
		le_uint64_t title_id;
		le_uint32_t version;
		byte_t main_thread_priority;
		byte_t main_thread_cpu_id;
		byte_t reserved_01;
		sFlag flags;
		sCodeSegment text;
		byte_t reserved_02[4];
		sCodeSegment ro;
		le_uint32_t main_thread_stack_size;
		sCodeSegment data;
		byte_t reserved_03[4];
		sCodeSegment bss;
		byte_t reserved_04[4];
		byte_t reserved_05[0x20];
		byte_t capabilities[kip::kKernCapabilitySize];
	};
	static_assert(sizeof(sKipHeader) == 0x100, "sKipHeader size.");
#pragma pack(pop)
}
}