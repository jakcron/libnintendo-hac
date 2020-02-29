#include <nn/hac/MetaUtil.h>
#include <sstream>
#include <iomanip>

std::string nn::hac::MetaUtil::getInstructionTypeAsString(nn::hac::meta::InstructionType type)
{
	std::stringstream ss;

	switch(type)
	{
	case (nn::hac::meta::INSTR_32BIT):
		ss << "32Bit";
		break;
	case (nn::hac::meta::INSTR_64BIT):
		ss << "64Bit";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)type;
		break;
	}

	return ss.str();
}

std::string nn::hac::MetaUtil::getProcAddressSpaceTypeAsString(nn::hac::meta::ProcAddrSpaceType type)
{
	std::stringstream ss;

	switch(type)
	{
	case (nn::hac::meta::ADDR_SPACE_64BIT):
		ss << "64Bit";
		break;
	case (nn::hac::meta::ADDR_SPACE_32BIT):
		ss << "32Bit";
		break;
	case (nn::hac::meta::ADDR_SPACE_32BIT_NO_RESERVED):
		ss << "32Bit no reserved";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)type;
		break;
	}

	return ss.str();
}