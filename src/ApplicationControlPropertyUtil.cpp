#include <nn/hac/ApplicationControlPropertyUtil.h>
#include <sstream>
#include <iomanip>

bool nn::hac::ApplicationControlPropertyUtil::validateSaveDataSizeMax(int64_t size, int64_t alignment)
{
	return (alignment != 0 && (size & (alignment - 1)) != 0) == false;
}

bool nn::hac::ApplicationControlPropertyUtil::validateSaveDataSize(int64_t size)
{
	return (size & 0x3fff) == 0;
}

std::string nn::hac::ApplicationControlPropertyUtil::getSaveDataSizeAsString(int64_t size)
{
	static const int64_t kKiloByte = 1024;
	static const int64_t kMegaByte = 1024 * 1024;

	std::stringstream ss;


	if (size < kKiloByte)
	{
		ss << size << " B";
	}
	else if (size < kMegaByte)
	{
		ss << (size/kKiloByte) << " KB";
	}
	else
	{
		ss << (size/kMegaByte) << " MB";
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getAocRegistrationTypeAsString(nn::hac::nacp::AocRegistrationType val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::AOC_AllOnLaunch):
		ss << "AllOnLaunch";
		break;
	case (nn::hac::nacp::AOC_OnDemand):
		ss << "OnDemand";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getAttributeFlagAsString(nn::hac::nacp::AttributeFlag val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::ATTR_None):
		ss << "None";
		break;
	case (nn::hac::nacp::ATTR_Demo):
		ss << "Demo";
		break;
	case (nn::hac::nacp::ATTR_RetailInteractiveDisplay):
		ss << "RetailInteractiveDisplay";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getCrashReportModeAsString(nn::hac::nacp::CrashReportMode val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::CREP_Deny):
		ss << "Deny";
		break;
	case (nn::hac::nacp::CREP_Allow):
		ss << "Allow";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getDataLossConfirmationAsString(nn::hac::nacp::DataLossConfirmation val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::DLOSS_None):
		ss << "None";
		break;
	case (nn::hac::nacp::DLOSS_Required):
		ss << "Required";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getHdcpAsString(nn::hac::nacp::Hdcp val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::HDCP_None):
		ss << "None";
		break;
	case (nn::hac::nacp::HDCP_Required):
		ss << "Required";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getLanguageAsString(nn::hac::nacp::Language val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::LANG_AmericanEnglish):
		ss << "AmericanEnglish";
		break;
	case (nn::hac::nacp::LANG_BritishEnglish):
		ss << "BritishEnglish";
		break;
	case (nn::hac::nacp::LANG_Japanese):
		ss << "Japanese";
		break;
	case (nn::hac::nacp::LANG_French):
		ss << "French";
		break;
	case (nn::hac::nacp::LANG_German):
		ss << "German";
		break;
	case (nn::hac::nacp::LANG_LatinAmericanSpanish):
		ss << "LatinAmericanSpanish";
		break;
	case (nn::hac::nacp::LANG_Spanish):
		ss << "Spanish";
		break;
	case (nn::hac::nacp::LANG_Italian):
		ss << "Italian";
		break;
	case (nn::hac::nacp::LANG_Dutch):
		ss << "Dutch";
		break;
	case (nn::hac::nacp::LANG_CanadianFrench):
		ss << "CanadianFrench";
		break;
	case (nn::hac::nacp::LANG_Portuguese):
		ss << "Portuguese";
		break;
	case (nn::hac::nacp::LANG_Russian):
		ss << "Russian";
		break;
	case (nn::hac::nacp::LANG_Korean):
		ss << "Korean";
		break;
	case (nn::hac::nacp::LANG_TraditionalChinese):
		ss << "TraditionalChinese";
		break;
	case (nn::hac::nacp::LANG_SimplifiedChinese):
		ss << "SimplifiedChinese";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getLogoHandlingAsString(nn::hac::nacp::LogoHandling val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::LHND_Auto):
		ss << "Auto";
		break;
	case (nn::hac::nacp::LHND_None):
		ss << "None";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getLogoTypeAsString(nn::hac::nacp::LogoType val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::LOGO_LicensedByNintendo):
		ss << "LicensedByNintendo";
		break;
	case (nn::hac::nacp::LOGO_DistributedByNintendo):
		ss << "DistributedByNintendo";
		break;
	case (nn::hac::nacp::LOGO_Nintendo):
		ss << "Nintendo";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getOrganisationAsString(nn::hac::nacp::Organisation val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::ORGN_CERO):
		ss << "CERO";
		break;
	case (nn::hac::nacp::ORGN_GRACGCRB):
		ss << "GRACGCRB";
		break;
	case (nn::hac::nacp::ORGN_GSRMR):
		ss << "GSRMR";
		break;
	case (nn::hac::nacp::ORGN_ESRB):
		ss << "ESRB";
		break;
	case (nn::hac::nacp::ORGN_ClassInd):
		ss << "ClassInd";
		break;
	case (nn::hac::nacp::ORGN_USK):
		ss << "USK";
		break;
	case (nn::hac::nacp::ORGN_PEGI):
		ss << "PEGI";
		break;
	case (nn::hac::nacp::ORGN_PEGIPortugal):
		ss << "PEGIPortugal";
		break;
	case (nn::hac::nacp::ORGN_PEGIBBFC):
		ss << "PEGIBBFC";
		break;
	case (nn::hac::nacp::ORGN_Russian):
		ss << "Russian";
		break;
	case (nn::hac::nacp::ORGN_ACB):
		ss << "ACB";
		break;
	case (nn::hac::nacp::ORGN_OFLC):
		ss << "OFLC";
		break;
	case (nn::hac::nacp::ORGN_IARCGeneric):
		ss << "IARCGeneric";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getParentalControlFlagAsString(nn::hac::nacp::ParentalControlFlag val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::PC_None):
		ss << "None";
		break;
	case (nn::hac::nacp::PC_FreeCommunication):
		ss << "FreeCommunication";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getPlayLogPolicyAsString(nn::hac::nacp::PlayLogPolicy val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::PLP_All):
		ss << "All";
		break;
	case (nn::hac::nacp::PLP_LogOnly):
		ss << "LogOnly";
		break;
	case (nn::hac::nacp::PLP_None):
		ss << "None";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getPlayLogQueryCapabilityAsString(nn::hac::nacp::PlayLogQueryCapability val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::PLQC_None):
		ss << "None";
		break;
	case (nn::hac::nacp::PLQC_Whitelist):
		ss << "Whitelist";
		break;
	case (nn::hac::nacp::PLQC_All):
		ss << "All";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getRepairFlagAsString(nn::hac::nacp::RepairFlag val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::REPF_None):
		ss << "None";
		break;
	case (nn::hac::nacp::REPF_SuppressGameCardAccess):
		ss << "SuppressGameCardAccess";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getRequiredNetworkServiceLicenseOnLaunchValueAsString(nn::hac::nacp::RequiredNetworkServiceLicenseOnLaunchValue val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::REQNETLIC_None):
		ss << "None";
		break;
	case (nn::hac::nacp::REQNETLIC_Common):
		ss << "Common";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getRuntimeAocInstallModeAsString(nn::hac::nacp::RuntimeAocInstallMode val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::RTAOC_Deny):
		ss << "Deny";
		break;
	case (nn::hac::nacp::RTAOC_AllowAppend):
		ss << "AllowAppend";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getScreenshotModeAsString(nn::hac::nacp::ScreenshotMode val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::SCRN_Allow):
		ss << "Allow";
		break;
	case (nn::hac::nacp::SCRN_Deny):
		ss << "Deny";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getStartupUserAccountAsString(nn::hac::nacp::StartupUserAccount val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::USER_None):
		ss << "None";
		break;
	case (nn::hac::nacp::USER_Required):
		ss << "Required";
		break;
	case (nn::hac::nacp::USER_RequiredWithNetworkServiceAccountAvailable):
		ss << "RequiredWithNetworkServiceAccountAvailable";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getTouchScreenUsageModeAsString(nn::hac::nacp::TouchScreenUsageMode val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::TOUCH_None):
		ss << "None";
		break;
	case (nn::hac::nacp::TOUCH_Supported):
		ss << "Supported";
		break;
	case (nn::hac::nacp::TOUCH_Required):
		ss << "Required";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getUserAccountSwitchLockValueAsString(nn::hac::nacp::UserAccountSwitchLockValue val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::UASL_Disable):
		ss << "Disable";
		break;
	case (nn::hac::nacp::UASL_Enable):
		ss << "Enable";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getVideoCaptureModeAsString(nn::hac::nacp::VideoCaptureMode val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::VCAP_Disable):
		ss << "Disable";
		break;
	case (nn::hac::nacp::VCAP_Manual):
		ss << "Manual";
		break;
	case (nn::hac::nacp::VCAP_Enable):
		ss << "Enable";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}