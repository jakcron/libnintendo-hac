#pragma once
#include <nn/hac/define/types.h>
#include <nn/hac/define/macro.h>

namespace nn
{
namespace hac
{
	namespace meta
	{
		static const uint32_t kMetaStructMagic = _MAKE_STRUCT_MAGIC_U32("META");
		static const size_t kNameMaxLen = 0x10;
		static const size_t kProductCodeMaxLen = 0x10;
		static const uint32_t kMaxPriority = _BIT(6) - 1;
		static const size_t kSectionAlignSize = 0x10;
		static const uint32_t kDefaultMainThreadStackSize = 4096;
		static const uint32_t kAlignSystemResourceSize = 0x200000;
		static const uint32_t kAlignSystemResourceMask = kAlignSystemResourceSize - 1;
		static const uint32_t kMaxSystemResourceSize = 0x1FE00000;

		enum class ProcessAddressSpace : byte_t
		{
			AddressSpace32Bit,
			AddressSpace64BitOld,
			AddressSpace32BitNoReserved,
			AddressSpace64Bit
		};
	}
#pragma pack(push,1)
	struct sMetaHeader
	{
		le_uint32_t st_magic;
		byte_t aci_desc_key_generation;
		byte_t reserved_0[7];
		struct sFlag
		{
			byte_t is_64bit_instruction : 1;
			byte_t process_address_space : 3;
			byte_t optimise_memory_allocation : 1; // if KernelCaps.MiscParams.ProgramType == Application && system_resource_size != 0 this will be set if MemoryAllocationCompatiblityMode is false
			byte_t :0;
		} flag;
		byte_t reserved_1;
		byte_t main_thread_priority;
		byte_t main_thread_cpu_id;
		byte_t reserved_2[4];
		le_uint32_t system_resource_size; // this can only be set if KernelCaps.MiscParams.ProgramType is Application or Applet and flag.process_address_space == AddressSpace64Bit. Using this makes SystemCalls MapPhysicalMemory & UnmapPhysicalMemory unavailable.
		le_uint32_t version; // sdk will set this to default_core_version if available
		le_uint32_t main_thread_stack_size;
		char name[meta::kNameMaxLen]; // important
		char product_code[meta::kProductCodeMaxLen]; // can be empty
		byte_t reserved_3[48];
		struct sSection
		{
			le_uint32_t offset;
			le_uint32_t size;
		} aci, aci_desc;
	};
	static_assert(sizeof(sMetaHeader) == 0x80, "sMetaHeader size");
#pragma pack(pop)
}
}