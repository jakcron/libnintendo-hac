#include <nn/hac/AccessControlInfoUtil.h>
#include <sstream>
#include <iomanip>

std::string nn::hac::AccessControlInfoUtil::getAcidFlagAsString(nn::hac::aci::AcidFlag flag)
{
	std::stringstream ss;

	switch(flag)
	{
	case (nn::hac::aci::FLAG_PRODUCTION):
		ss << "Production";
		break;
	case (nn::hac::aci::FLAG_UNQUALIFIED_APPROVAL):
		ss << "UnqualifiedApproval";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)flag;
		break;
	}

	return ss.str();
}