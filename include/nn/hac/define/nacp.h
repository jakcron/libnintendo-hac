#pragma once
#include <fnd/types.h>

namespace nn
{
namespace hac
{
	namespace nacp
	{
		static const size_t kNameLength = 0x200;
		static const size_t kPublisherLength = 0x100;
		static const size_t kMaxLanguageCount = 16;
		static const size_t kIsbnLength = 37;
		static const size_t kRatingAgeCount = 32;
		static const size_t kDisplayVersionLength = 16;
		static const size_t kApplicationErrorCodeCategoryLength = 8;
		static const size_t kLocalCommunicationIdCount = 8;
		static const size_t kBcatPassphraseLength = 65;
		static const size_t kPlayLogQueryableApplicationIdCount = 16;
		static const int8_t kUnusedAgeRating = -1;
		static const size_t kNeighborDetectionGroupConfigurationKeyLength = 16;
		static const size_t kReceivableGroupConfigurationCount = 16;
		static const uint64_t kDefaultJitMemorySize = 0x400000;
		static const uint64_t kJitMemoryMultipleSize = 0x200000;
		static const uint64_t kBcatAlignmentMask = 0xFFFFF; // cannot have size that isn't a multiple of 1MiB
		static const uint64_t kBcatMiniumSize = 0x500000; // cannot have a size (non zero) that is smaller than 5MiB
		static const uint64_t kSaveDataAlignmentMask = 0x3FFF; // cannot have a size that isn't a multiple of 16KiB

		enum class AddOnContentRegistrationType : byte_t
		{
			AllOnLaunch,
			OnDemand
		};

		enum class AttributeFlag : byte_t
		{
			Demo,
			RetailInteractiveDisplay
		};

		enum class CrashReport : byte_t
		{
			Deny,
			Allow
		};

		enum class DataLossConfirmation : byte_t
		{
			None,
			Required
		};

		enum class Hdcp : byte_t
		{
			None,
			Required
		};

		enum class JitConfigurationFlag : uint64_t
		{
			Enabled
		};

		enum class Language : byte_t
		{
			AmericanEnglish,
			BritishEnglish,
			Japanese,
			French,
			German,
			LatinAmericanSpanish,
			Spanish,
			Italian,
			Dutch,
			CanadianFrench,
			Portuguese,
			Russian,
			Korean,
			TraditionalChinese,
			SimplifiedChinese,

			// Deprecated names
			Taiwanese = TraditionalChinese,
			Chinese = SimplifiedChinese
		};

		enum class LogoHandling : byte_t
		{
			Auto,
			None
		};

		enum class LogoType : byte_t
		{
			LicensedByNintendo = 0,
			DistributedByNintendo = 1, // Removed in SDK 3.5.2
			Nintendo = 2
		};

		enum class Organisation : byte_t
		{
			CERO,
			GRACGCRB,
			GSRMR,
			ESRB,
			ClassInd,
			USK,
			PEGI,
			PEGIPortugal,
			PEGIBBFC,
			Russian,
			ACB,
			OFLC,
			IARCGeneric
		};

		enum class ParentalControlFlag : uint32_t
		{
			FreeCommunication
		};

		enum class PlayLogPolicy : byte_t
		{
			All,
			LogOnly,
			None
		};

		enum class PlayLogQueryCapability : byte_t
		{
			None,
			Whitelist,
			All
		};

		enum class RepairFlag : byte_t
		{
			SuppressGameCardAccess
		};

		enum class RequiredNetworkServiceLicenseOnLaunchFlag : byte_t
		{
			Common
		};

		enum class RuntimeAddOnContentInstall : byte_t
		{
			Deny,
			AllowAppend
		};

		enum class RuntimeParameterDelivery : byte_t
		{
			Always,
			AlwaysIfUserStateMatched,
			OnRestart
		};

		enum class Screenshot : byte_t
		{
			Allow,
			Deny
		};

		enum class StartupUserAccountOptionFlag : byte_t
		{
			IsOptional
		};

		enum class StartupUserAccount : byte_t
		{
			None,
			Required,
			RequiredWithNetworkServiceAccountAvailable
		};

		enum class TouchScreenUsage : byte_t
		{
			None,
			Supported,
			Required,
		};

		enum class UserAccountSwitchLock : byte_t
		{
			Disable,
			Enable
		};

		enum class VideoCapture : byte_t
		{
			Disable,
			Manual,
			Enable,

			// Deprecated names
			Deny = Disable,
			Allow = Manual
		};
	}


#pragma pack(push,1)
	struct sApplicationControlProperty
	{
		struct sTitle
		{
			char name[nacp::kNameLength];
			char publisher[nacp::kPublisherLength];
		} title[nacp::kMaxLanguageCount];
		char isbn[nacp::kIsbnLength];
		byte_t startup_user_account;
		byte_t user_account_switch_lock;
		byte_t add_on_content_registration_type;
		le_uint32_t attribute_flag;
		le_uint32_t supported_language_flag;
		le_uint32_t parental_control_flag;
		byte_t screenshot;
		byte_t video_capture;
		byte_t data_loss_confirmation;
		byte_t play_log_policy;
		le_uint64_t presence_group_id;
		int8_t rating_age[nacp::kRatingAgeCount];
		char display_version[nacp::kDisplayVersionLength];
		le_uint64_t add_on_content_base_id;
		le_uint64_t save_data_owner_id;
		le_uint64_t user_account_save_data_size;
		le_uint64_t user_account_save_data_journal_size;
		le_uint64_t device_save_data_size;
		le_uint64_t device_save_data_journal_size;
		le_uint64_t bcat_delivery_cache_storage_size;
		char application_error_code_category[nacp::kApplicationErrorCodeCategoryLength];
		le_uint64_t local_communication_id[nacp::kLocalCommunicationIdCount];
		byte_t logo_type;
		byte_t logo_handling;
		byte_t runtime_add_on_content_install;
		byte_t runtime_parameter_delivery;
		byte_t reserved_00[2];
		byte_t crash_report;
		byte_t hdcp;
		le_uint64_t seed_for_pseudo_device_id;
		char bcat_passphrase[nacp::kBcatPassphraseLength];
		byte_t startup_user_account_option;
		byte_t reserved_01[6]; //reserved_for_user_account_save_data_operation
		le_uint64_t user_account_save_data_size_max;
		le_uint64_t user_account_save_data_journal_size_max;
		le_uint64_t device_save_data_size_max;
		le_uint64_t device_save_data_journal_size_max;
		le_uint64_t temporary_storage_size;
		le_uint64_t cache_storage_size;
		le_uint64_t cache_storage_journal_size;
		le_uint64_t cache_storage_data_and_journal_size_max;
		le_uint16_t cache_storage_index_max;
		byte_t reserved_02[6];
		le_uint64_t play_log_queryable_application_id[nacp::kPlayLogQueryableApplicationIdCount];
		byte_t play_log_query_capability;
		byte_t repair_flag;
		byte_t program_index;
		byte_t required_network_service_license_on_launch_flag;
		byte_t reserved_03[0x4];
		struct sNeighborDetectionClientConfiguration
		{
			struct sGroupConfiguration
			{
				le_uint64_t group_id;
				byte_t key[nacp::kNeighborDetectionGroupConfigurationKeyLength];
			};

			sGroupConfiguration send_group_configuration;
			sGroupConfiguration receivable_group_configuration[nacp::kReceivableGroupConfigurationCount];
		} neighbour_detection_client_configuration;
		struct sJitConfiguration 
		{
			le_uint64_t jit_configuration_flag;
			le_uint64_t memory_size;
		} jit_configuration;
		byte_t reserved_04[0xC40];
	};
	static_assert(sizeof(sApplicationControlProperty) == 0x4000, "sApplicationControlProperty size.");

	struct sApplicationControlProperty_v0
	{
		struct sTitle
		{
			char name[nacp::kNameLength];
			char publisher[nacp::kPublisherLength];
		} title[nacp::kMaxLanguageCount];
		char isbn[nacp::kIsbnLength];
		byte_t startup_user_account;
		byte_t touch_screen_usage;
		byte_t add_on_content_registration_type;
		le_uint32_t attribute_flag;
		le_uint32_t supported_language_flag;
		le_uint32_t parental_control_flag;
		byte_t screenshot;
		byte_t video_capture;
		byte_t data_loss_confirmation;
		byte_t play_log_policy;
		le_uint64_t presence_group_id;
		int8_t rating_age[nacp::kRatingAgeCount];
		char display_version[nacp::kDisplayVersionLength];
		le_uint64_t add_on_content_base_id;
		le_uint64_t save_data_owner_id;
		le_uint64_t user_account_save_data_size;
		le_uint64_t user_account_save_data_journal_size;
		le_uint64_t device_save_data_size;
		le_uint64_t device_save_data_journal_size;
		le_uint64_t bcat_delivery_cache_storage_size;
		char application_error_code_category[nacp::kApplicationErrorCodeCategoryLength];
		le_uint64_t local_communication_id[nacp::kLocalCommunicationIdCount];
		byte_t logo_type;
		byte_t logo_handling;
		byte_t runtime_add_on_content_install;
		byte_t reserved_00[3];
		byte_t crash_report;
		byte_t hdcp;
		le_uint64_t seed_for_pseudo_device_id;
		char bcat_passphrase[nacp::kBcatPassphraseLength];
		byte_t reserved_01;
		byte_t reserved_02[6]; //reserved_for_user_account_save_data_operation
		le_uint64_t user_account_save_data_size_max;
		le_uint64_t user_account_save_data_journal_size_max;
		le_uint64_t device_save_data_size_max;
		le_uint64_t device_save_data_journal_size_max;
		le_uint64_t temporary_storage_size;
		le_uint64_t cache_storage_size;
		le_uint64_t cache_storage_journal_size;
		le_uint64_t cache_storage_data_and_journal_size_max;
		le_uint16_t cache_storage_index_max;
		byte_t reserved_03[6];
		le_uint64_t play_log_queryable_application_id[nacp::kPlayLogQueryableApplicationIdCount];
		byte_t play_log_query_capability;
		byte_t repair_flag;
		byte_t program_index;
		byte_t reserved_04[0xDED];
	};
	static_assert(sizeof(sApplicationControlProperty_v0) == 0x4000, "sApplicationControlProperty_v0 size.");

#pragma pack(pop)
}
}