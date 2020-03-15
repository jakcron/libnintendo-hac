#include <nn/hac/ContentMetaUtil.h>
#include <sstream>
#include <iomanip>

std::string nn::hac::ContentMetaUtil::getContentTypeAsString(nn::hac::cnmt::ContentType val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::cnmt::ContentType::Meta):
		ss << "Meta";
		break;
	case (nn::hac::cnmt::ContentType::Program):
		ss << "Program";
		break;
	case (nn::hac::cnmt::ContentType::Data):
		ss << "Data";
		break;
	case (nn::hac::cnmt::ContentType::Control):
		ss << "Control";
		break;
	case (nn::hac::cnmt::ContentType::HtmlDocument):
		ss << "HtmlDocument";
		break;
	case (nn::hac::cnmt::ContentType::LegalInformation):
		ss << "LegalInformation";
		break;
	case (nn::hac::cnmt::ContentType::DeltaFragment):
		ss << "DeltaFragment";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ContentMetaUtil::getContentMetaTypeAsString(nn::hac::cnmt::ContentMetaType val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::cnmt::ContentMetaType::SystemProgram):
		ss << "SystemProgram";
		break;
	case (nn::hac::cnmt::ContentMetaType::SystemData):
		ss << "SystemData";
		break;
	case (nn::hac::cnmt::ContentMetaType::SystemUpdate):
		ss << "SystemUpdate";
		break;
	case (nn::hac::cnmt::ContentMetaType::BootImagePackage):
		ss << "BootImagePackage";
		break;
	case (nn::hac::cnmt::ContentMetaType::BootImagePackageSafe):
		ss << "BootImagePackageSafe";
		break;
	case (nn::hac::cnmt::ContentMetaType::Application):
		ss << "Application";
		break;
	case (nn::hac::cnmt::ContentMetaType::Patch):
		ss << "Patch";
		break;
	case (nn::hac::cnmt::ContentMetaType::AddOnContent):
		ss << "AddOnContent";
		break;
	case (nn::hac::cnmt::ContentMetaType::Delta):
		ss << "Delta";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ContentMetaUtil::getUpdateTypeAsString(nn::hac::cnmt::UpdateType val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::cnmt::UpdateType::ApplyAsDelta):
		ss << "ApplyAsDelta";
		break;
	case (nn::hac::cnmt::UpdateType::Overwrite):
		ss << "Overwrite";
		break;
	case (nn::hac::cnmt::UpdateType::Create):
		ss << "Create";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ContentMetaUtil::getContentMetaAttributeFlagAsString(nn::hac::cnmt::ContentMetaAttributeFlag val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::cnmt::ContentMetaAttributeFlag::IncludesExFatDriver):
		ss << "IncludesExFatDriver";
		break;
	case (nn::hac::cnmt::ContentMetaAttributeFlag::Rebootless):
		ss << "Rebootless";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}