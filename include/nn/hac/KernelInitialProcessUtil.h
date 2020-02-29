#pragma once
#include <nn/hac/define/kip.h>
#include <string>

namespace nn
{
namespace hac
{
	class KernelInitialProcessUtil
	{
	public:
		static std::string getProcessCategoryAsString(nn::hac::kip::ProcessCategory val);

	private:
		const std::string kModuleName = "KERNEL_INITIAL_PROCESS_UTIL";
	};
}
}