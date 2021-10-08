#pragma once
#include <tc/io/VirtualFileSystem.h>

namespace nn { namespace hac {

struct GameCardFsMetaGenerator : public tc::io::VirtualFileSystem::FileSystemMeta
{
public:
	enum ValidationMode
	{
		ValidationMode_None,
		ValidationMode_Warn,
		ValidationMode_Throw
	};

	GameCardFsMetaGenerator(const std::shared_ptr<tc::io::IStream>& stream, size_t root_header_size, ValidationMode validate_mode = ValidationMode_Warn);
private:
	GameCardFsMetaGenerator();
};

}} // namespace nn::hac