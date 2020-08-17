#pragma once
#include <nn/hac/define/types.h>

namespace nn
{
namespace hac
{
	namespace compression
	{
		// defines
		static const size_t kRomfsBlockSize = 0x10000;
		static const size_t kRomfsBlockAlign = 0x10;

		// enums
		enum class CompressionType : byte_t
		{
			None,
			Lz4
		};
	}
	
#pragma pack(push,1)
	// structures
	struct sCompressionEntry
	{
		le_uint64_t virtual_offset;
		le_uint64_t physical_offset;
		byte_t compression_type;
		byte_t reserved[3];
		le_uint32_t physical_size;
	};
	static_assert(sizeof(sCompressionEntry) == 24, "sCompressionEntry size.");

#pragma pack(pop)
}
}