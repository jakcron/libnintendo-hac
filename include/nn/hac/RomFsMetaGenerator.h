#pragma once
#include <tc/io/VirtualFileSystem.h>

#include <nn/hac/define/romfs.h>

namespace nn { namespace hac {

struct RomFsMetaGenerator : public tc::io::VirtualFileSystem::FileSystemMeta
{
public:
	RomFsMetaGenerator(const std::shared_ptr<tc::io::IStream>& stream);
private:
	RomFsMetaGenerator();

	std::shared_ptr<tc::io::IStream> mBaseStream;

	int64_t mDataOffset;

	tc::ByteData mDirEntryTable;
	std::map<uint32_t, size_t> mDirParentVaddrMap;
	inline nn::hac::sRomfsDirEntry* getDirEntry(uint32_t vaddr) { return (nn::hac::sRomfsDirEntry*)(mDirEntryTable.data() + vaddr); }

	tc::ByteData mFileEntryTable;
	inline nn::hac::sRomfsFileEntry* getFileEntry(uint32_t vaddr) { return (nn::hac::sRomfsFileEntry*)(mFileEntryTable.data() + vaddr); }

	//void addFile(const nn::hac::sRomfsFileEntry* file_entry, size_t parent_dir);
	//void addDirectory(const nn::hac::sRomfsDirEntry* dir_entry, size_t parent_dir);
};

}} // namespace nn::hac