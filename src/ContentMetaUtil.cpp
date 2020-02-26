#include <nn/hac/ContentMetaUtil.h>
#include <sstream>
#include <iomanip>

std::string nn::hac::ContentMetaUtil::getContentTypeAsString(nn::hac::cnmt::ContentType val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::cnmt::TYPE_META):
		ss << "Meta";
		break;
	case (nn::hac::cnmt::TYPE_PROGRAM):
		ss << "Program";
		break;
	case (nn::hac::cnmt::TYPE_DATA):
		ss << "Data";
		break;
	case (nn::hac::cnmt::TYPE_CONTROL):
		ss << "Control";
		break;
	case (nn::hac::cnmt::TYPE_HTML_DOCUMENT):
		ss << "HtmlDocument";
		break;
	case (nn::hac::cnmt::TYPE_LEGAL_INFORMATION):
		ss << "LegalInformation";
		break;
	case (nn::hac::cnmt::TYPE_DELTA_FRAGMENT):
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
	case (nn::hac::cnmt::METATYPE_SYSTEM_PROGRAM):
		ss << "SystemProgram";
		break;
	case (nn::hac::cnmt::METATYPE_SYSTEM_DATA):
		ss << "SystemData";
		break;
	case (nn::hac::cnmt::METATYPE_SYSTEM_UPDATE):
		ss << "SystemUpdate";
		break;
	case (nn::hac::cnmt::METATYPE_BOOT_IMAGE_PACKAGE):
		ss << "BootImagePackage";
		break;
	case (nn::hac::cnmt::METATYPE_BOOT_IMAGE_PACKAGE_SAFE):
		ss << "BootImagePackageSafe";
		break;
	case (nn::hac::cnmt::METATYPE_APPLICATION):
		ss << "Application";
		break;
	case (nn::hac::cnmt::METATYPE_PATCH):
		ss << "Patch";
		break;
	case (nn::hac::cnmt::METATYPE_ADD_ON_CONTENT):
		ss << "AddOnContent";
		break;
	case (nn::hac::cnmt::METATYPE_DELTA):
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
	case (nn::hac::cnmt::UPDATETYPE_APPLY_AS_DELTA):
		ss << "ApplyAsDelta";
		break;
	case (nn::hac::cnmt::UPDATETYPE_OVERWRITE):
		ss << "Overwrite";
		break;
	case (nn::hac::cnmt::UPDATETYPE_CREATE):
		ss << "Create";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ContentMetaUtil::getContentMetaAttributeAsString(nn::hac::cnmt::ContentMetaAttribute val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::cnmt::ATTRIBUTE_INCLUDES_EX_FAT_DRIVER):
		ss << "IncludesExFatDriver";
		break;
	case (nn::hac::cnmt::ATTRIBUTE_REBOOTLESS):
		ss << "Rebootless";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}