#pragma once
#include <nn/hac/define/nacp.h>

namespace nn
{
namespace hac
{
	class ApplicationControlPropertyUtil
	{
	public:
		static bool validateSaveDataSizeMax(int64_t size, int64_t alignment);
		static bool validateSaveDataSize(int64_t size);
		static std::string getSaveDataSizeAsString(int64_t size);

		static std::string getAocRegistrationTypeAsString(nn::hac::nacp::AocRegistrationType val);
		static std::string getAttributeFlagAsString(nn::hac::nacp::AttributeFlag val);
		static std::string getCrashReportModeAsString(nn::hac::nacp::CrashReportMode val);
		static std::string getDataLossConfirmationAsString(nn::hac::nacp::DataLossConfirmation val);
		static std::string getHdcpAsString(nn::hac::nacp::Hdcp val);
		static std::string getLanguageAsString(nn::hac::nacp::Language val);
		static std::string getLogoHandlingAsString(nn::hac::nacp::LogoHandling val);
		static std::string getLogoTypeAsString(nn::hac::nacp::LogoType val);
		static std::string getOrganisationAsString(nn::hac::nacp::Organisation val);
		static std::string getParentalControlFlagAsString(nn::hac::nacp::ParentalControlFlag val);
		static std::string getPlayLogPolicyAsString(nn::hac::nacp::PlayLogPolicy val);
		static std::string getPlayLogQueryCapabilityAsString(nn::hac::nacp::PlayLogQueryCapability val);
		static std::string getRepairFlagAsString(nn::hac::nacp::RepairFlag val);
		static std::string getRequiredNetworkServiceLicenseOnLaunchValueAsString(nn::hac::nacp::RequiredNetworkServiceLicenseOnLaunchValue val);
		static std::string getRuntimeAocInstallModeAsString(nn::hac::nacp::RuntimeAocInstallMode val);
		static std::string getScreenshotModeAsString(nn::hac::nacp::ScreenshotMode val);
		static std::string getStartupUserAccountAsString(nn::hac::nacp::StartupUserAccount val);
		static std::string getTouchScreenUsageModeAsString(nn::hac::nacp::TouchScreenUsageMode val);
		static std::string getUserAccountSwitchLockValueAsString(nn::hac::nacp::UserAccountSwitchLockValue val);
		static std::string getVideoCaptureModeAsString(nn::hac::nacp::VideoCaptureMode val);
	};
}
}