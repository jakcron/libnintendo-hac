#pragma once
#include <tc/io/VirtualFileSystem.h>

namespace nn { namespace hac {

struct PartitionFsMetaGenerator : public tc::io::VirtualFileSystem::FileSystemMeta
{
public:
	enum ValidationMode
	{
		ValidationMode_None,
		ValidationMode_Warn,
		ValidationMode_Throw
	};

	PartitionFsMetaGenerator(const std::shared_ptr<tc::io::IStream>& stream, ValidationMode validate_mode = ValidationMode_Warn);
private:
	PartitionFsMetaGenerator();
};

}} // namespace nn::hac