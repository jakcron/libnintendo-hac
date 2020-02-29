#pragma once
#include <nn/hac/define/meta.h>
#include <string>

namespace nn
{
namespace hac
{
	class MetaUtil
	{
	public:
		static std::string getInstructionTypeAsString(nn::hac::meta::InstructionType type);
		static std::string getProcAddressSpaceTypeAsString(nn::hac::meta::ProcAddrSpaceType type);

	private:
		const std::string kModuleName = "META_UTIL";
	};
}
}