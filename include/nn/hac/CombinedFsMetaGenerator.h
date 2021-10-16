#pragma once
#include <tc/io/VirtualFileSystem.h>

namespace nn { namespace hac {

struct CombinedFsMetaGenerator : public tc::io::VirtualFileSystem::FileSystemMeta
{
public:
	struct MountPointInfo
	{
		std::string name;
		tc::io::VirtualFileSystem::FileSystemMeta fs_meta;
	};

	CombinedFsMetaGenerator(const std::vector<MountPointInfo>& mount_point_info);
private:
	CombinedFsMetaGenerator();
};

}} // namespace nn::hac