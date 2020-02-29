#include <nn/hac/AccessControlInfoUtil.h>
#include <sstream>
#include <iomanip>

std::string nn::hac::AccessControlInfoUtil::getAcidFlagAsString(nn::hac::aci::AcidFlag flag)
{
	std::stringstream ss;

	switch(flag)
	{
	case (nn::hac::aci::ACIDFLAG_PRODUCTION):
		ss << "Production";
		break;
	case (nn::hac::aci::ACIDFLAG_UNQUALIFIED_APPROVAL):
		ss << "UnqualifiedApproval";
		break;
	case (nn::hac::aci::ACIDFLAG_MEMORY_REGION_RESERVED_BIT0):
		ss << "MemoryRegion_ReservedBit0";
		break;
	case (nn::hac::aci::ACIDFLAG_MEMORY_REGION_RESERVED_BIT1):
		ss << "MemoryRegion_ReservedBit1";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)flag;
		break;
	}

	return ss.str();
}

std::string nn::hac::AccessControlInfoUtil::getMemoryRegionAsString(nn::hac::aci::MemoryRegion mem_region)
{
	std::stringstream ss;

	switch(mem_region)
	{
	case (nn::hac::aci::MEMREGION_APPLICATION):
		ss << "Application";
		break;
	case (nn::hac::aci::MEMREGION_APPLET):
		ss << "Applet";
		break;
	case (nn::hac::aci::MEMREGION_SECURE_SYSTEM):
		ss << "SecureSystem";
		break;
	case (nn::hac::aci::MEMREGION_NON_SECURE_SYSTEM):
		ss << "NonSecureSystem";
		break;
	default:
		ss << "unk_0x" << std::hex << (uint32_t)mem_region;
		break;
	}

	return ss.str();
}