#pragma once
#include <fnd/types.h>
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
		static const uint32_t kMaxPriority = BIT(6) - 1;
		static const size_t kSectionAlignSize = 0x10;
		static const uint32_t kDefaultMainThreadStackSize = 4096;

		enum class ProcessAddressSpace
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
			byte_t optimise_memory_allocation : 1;
			byte_t :0;
		} flag;
		byte_t reserved_1;
		byte_t main_thread_priority;
		byte_t main_thread_cpu_id;
		byte_t reserved_2[8];
		le_uint32_t version;
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