#pragma once
#include <nn/hac/define/types.h>

namespace nn
{
namespace hac
{
	namespace romfs
	{
		static const uint64_t kRomfsHeaderAlign = 0x200;
		static const uint32_t kInvalidAddr = 0xffffffff;

		enum HeaderSectionIndex
		{
			DIR_HASHMAP_TABLE,
			DIR_NODE_TABLE,
			FILE_HASHMAP_TABLE,
			FILE_NODE_TABLE,
			SECTION_NUM
		};
	}
	
#pragma pack(push,1)
	struct sRomfsHeader
	{
		tc::bn::le64<uint64_t> header_size;
		struct sSection
		{
			tc::bn::le64<uint64_t> offset;
			tc::bn::le64<uint64_t> size;
		} sections[romfs::SECTION_NUM];
		tc::bn::le64<uint64_t> data_offset;
	};
	static_assert(sizeof(sRomfsHeader) == 0x50, "sRomfsHeader size.");

	struct sRomfsDirEntry
	{
		tc::bn::le32<uint32_t> parent;
		tc::bn::le32<uint32_t> sibling;
		tc::bn::le32<uint32_t> child;
		tc::bn::le32<uint32_t> file;
		tc::bn::le32<uint32_t> hash;
		tc::bn::le32<uint32_t> name_size;
		char* name() { return ((char*)(this)) + sizeof(sRomfsDirEntry); }
		const char* name() const { return ((char*)(this)) + sizeof(sRomfsDirEntry); }
	};
	static_assert(sizeof(sRomfsDirEntry) == 0x18, "sRomfsDirEntry size.");

	struct sRomfsFileEntry
	{
		tc::bn::le32<uint32_t> parent;
		tc::bn::le32<uint32_t> sibling;
		tc::bn::le64<uint64_t> offset;
		tc::bn::le64<uint64_t> size;
		tc::bn::le32<uint32_t> hash;
		tc::bn::le32<uint32_t> name_size;
		char* name() { return ((char*)(this)) + sizeof(sRomfsFileEntry); }
		const char* name() const { return ((char*)(this)) + sizeof(sRomfsFileEntry); }
	};
	static_assert(sizeof(sRomfsFileEntry) == 0x20, "sRomfsFileEntry size.");
#pragma pack(pop)
}
}