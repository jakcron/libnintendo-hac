#pragma once
#include <nn/hac/define/aci.h>
#include <string>

namespace nn
{
namespace hac
{
	class AccessControlInfoUtil
	{
	public:
		static std::string getAcidFlagAsString(nn::hac::aci::AcidFlag flag);

	private:
		const std::string kModuleName = "ACCESS_CONTROL_INFO_UTIL";
	};
}
}