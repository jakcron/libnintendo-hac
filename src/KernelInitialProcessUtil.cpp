#include <nn/hac/KernelInitialProcessUtil.h>
#include <sstream>
#include <iomanip>

std::string nn::hac::KernelInitialProcessUtil::getProcessCategoryAsString(nn::hac::kip::ProcessCategory val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::kip::PROCCAT_REGULAR):
		ss << "NormalProcess";
		break;
	case (nn::hac::kip::PROCCAT_KERNAL_KIP):
		ss << "KernelInitalProcess";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}