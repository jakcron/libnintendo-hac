#pragma once
#include <nn/hac/define/kc.h>
#include <string>

namespace nn
{
namespace hac
{
	class KernelCapabilityUtil
	{
	public:
		static std::string getMiscFlagAsString(nn::hac::kc::MiscFlags flag);
		static std::string getMemMapPermAsString(nn::hac::kc::MemoryPerm type);
		static std::string getMemMapTypeAsString(nn::hac::kc::MappingType type);
		static std::string getSystemCallAsString(nn::hac::kc::SystemCall svc);

	private:
		const std::string kModuleName = "KERNEL_CAPABILITY_UTIL";
	};
}
}