#pragma once
#include <nn/hac/define/nrr.h>
#include <string>

namespace nn
{
namespace hac
{
	class NrrUtil
	{
	public:
		static std::string getNrrKindAsString(nn::hac::nrr::NrrKind val);

	private:
		const std::string kModuleName = "META_UTIL";
	};
}
}