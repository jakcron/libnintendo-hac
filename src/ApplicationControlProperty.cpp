#include <cstring>
#include <nn/hac/ApplicationControlProperty.h>

nn::hac::ApplicationControlProperty::ApplicationControlProperty()
{
	clear();
}

nn::hac::ApplicationControlProperty::ApplicationControlProperty(const ApplicationControlProperty& other)
{
	*this = other;
}

void nn::hac::ApplicationControlProperty::operator=(const ApplicationControlProperty& other)
{
	clear();
	mTitle = other.mTitle;
	mIsbn = other.mIsbn;
	mStartupUserAccount = other.mStartupUserAccount;
	mUserAccountSwitchLock = other.mUserAccountSwitchLock;
	mAddOnContentRegistrationType = other.mAddOnContentRegistrationType;
	mAttribute = other.mAttribute;
	mSupportedLanguage = other.mSupportedLanguage;
	mParentalControl = other.mParentalControl;
	mScreenshot = other.mScreenshot;
	mVideoCapture = other.mVideoCapture;
	mDataLossConfirmation = other.mDataLossConfirmation;
	mPlayLogPolicy = other.mPlayLogPolicy;
	mPresenceGroupId = other.mPresenceGroupId;
	mRatingAge = other.mRatingAge;
	mDisplayVersion = other.mDisplayVersion;
	mAddOnContentBaseId = other.mAddOnContentBaseId;
	mSaveDatawOwnerId = other.mSaveDatawOwnerId;
	mUserAccountSaveDataSize = other.mUserAccountSaveDataSize;
	mDeviceSaveDataSize = other.mDeviceSaveDataSize;
	mBcatDeliveryCacheStorageSize = other.mBcatDeliveryCacheStorageSize;
	mApplicationErrorCodeCategory = other.mApplicationErrorCodeCategory;
	mLocalCommunicationId = other.mLocalCommunicationId;
	mLogoType = other.mLogoType;
	mLogoHandling = other.mLogoHandling;
	mRuntimeAddOnContentInstall = other.mRuntimeAddOnContentInstall;
	mRuntimeParameterDelivery = other.mRuntimeParameterDelivery;
	mCrashReport = other.mCrashReport;
	mHdcp = other.mHdcp;
	mSeedForPsuedoDeviceId = other.mSeedForPsuedoDeviceId;
	mBcatPassphase = other.mBcatPassphase;
	mStartupUserAccountOption = other.mStartupUserAccountOption;
	mUserAccountSaveDataMax = other.mUserAccountSaveDataMax;
	mDeviceSaveDataMax = other.mDeviceSaveDataMax;
	mTemporaryStorageSize = other.mTemporaryStorageSize;
	mCacheStorageSize = other.mCacheStorageSize;
	mCacheStorageDataAndJournalSizeMax = other.mCacheStorageDataAndJournalSizeMax;
	mCacheStorageIndexMax = other.mCacheStorageIndexMax;
	mPlayLogQueryableApplicationId = other.mPlayLogQueryableApplicationId;
	mPlayLogQueryCapability = other.mPlayLogQueryCapability;
	mRepair = other.mRepair;
	mProgramIndex = other.mProgramIndex;
	mRequiredNetworkServiceLicenseOnLaunch = other.mRequiredNetworkServiceLicenseOnLaunch;
	mNeighborDetectionClientConfiguration = other.mNeighborDetectionClientConfiguration;
	mJitConfiguration = other.mJitConfiguration;
}

bool nn::hac::ApplicationControlProperty::operator==(const ApplicationControlProperty& other) const
{
	return (mTitle == other.mTitle) \
		&& (mIsbn == other.mIsbn) \
		&& (mStartupUserAccount == other.mStartupUserAccount) \
		&& (mUserAccountSwitchLock == other.mUserAccountSwitchLock) \
		&& (mAddOnContentRegistrationType == other.mAddOnContentRegistrationType) \
		&& (mAttribute == other.mAttribute) \
		&& (mSupportedLanguage == other.mSupportedLanguage) \
		&& (mParentalControl == other.mParentalControl) \
		&& (mScreenshot == other.mScreenshot) \
		&& (mVideoCapture == other.mVideoCapture) \
		&& (mDataLossConfirmation == other.mDataLossConfirmation) \
		&& (mPlayLogPolicy == other.mPlayLogPolicy) \
		&& (mPresenceGroupId == other.mPresenceGroupId) \
		&& (mRatingAge == other.mRatingAge) \
		&& (mDisplayVersion == other.mDisplayVersion) \
		&& (mAddOnContentBaseId == other.mAddOnContentBaseId) \
		&& (mSaveDatawOwnerId == other.mSaveDatawOwnerId) \
		&& (mUserAccountSaveDataSize == other.mUserAccountSaveDataSize) \
		&& (mDeviceSaveDataSize == other.mDeviceSaveDataSize) \
		&& (mBcatDeliveryCacheStorageSize == other.mBcatDeliveryCacheStorageSize) \
		&& (mApplicationErrorCodeCategory == other.mApplicationErrorCodeCategory) \
		&& (mLocalCommunicationId == other.mLocalCommunicationId) \
		&& (mLogoType == other.mLogoType) \
		&& (mLogoHandling == other.mLogoHandling) \
		&& (mRuntimeAddOnContentInstall == other.mRuntimeAddOnContentInstall) \
		&& (mRuntimeParameterDelivery == other.mRuntimeParameterDelivery) \
		&& (mCrashReport == other.mCrashReport) \
		&& (mHdcp == other.mHdcp) \
		&& (mSeedForPsuedoDeviceId == other.mSeedForPsuedoDeviceId) \
		&& (mBcatPassphase == other.mBcatPassphase) \
		&& (mStartupUserAccountOption == other.mStartupUserAccountOption) \
		&& (mUserAccountSaveDataMax == other.mUserAccountSaveDataMax) \
		&& (mDeviceSaveDataMax == other.mDeviceSaveDataMax) \
		&& (mTemporaryStorageSize == other.mTemporaryStorageSize) \
		&& (mCacheStorageSize == other.mCacheStorageSize) \
		&& (mCacheStorageDataAndJournalSizeMax == other.mCacheStorageDataAndJournalSizeMax) \
		&& (mCacheStorageIndexMax == other.mCacheStorageIndexMax) \
		&& (mPlayLogQueryableApplicationId == other.mPlayLogQueryableApplicationId) \
		&& (mPlayLogQueryCapability == other.mPlayLogQueryCapability) \
		&& (mRepair == other.mRepair) \
		&& (mProgramIndex == other.mProgramIndex) \
		&& (mRequiredNetworkServiceLicenseOnLaunch == other.mRequiredNetworkServiceLicenseOnLaunch) \
		&& (mNeighborDetectionClientConfiguration == other.mNeighborDetectionClientConfiguration) \
		&& (mJitConfiguration == other.mJitConfiguration);
}

bool nn::hac::ApplicationControlProperty::operator!=(const ApplicationControlProperty& other) const
{
	return !(*this == other);
}

void nn::hac::ApplicationControlProperty::toBytes()
{
	mRawBinary.alloc(sizeof(nn::hac::sApplicationControlProperty));

	sApplicationControlProperty* nacp = (sApplicationControlProperty*)mRawBinary.data();

	// strings
	for (size_t i = 0; i < mTitle.size(); i++)
	{
		strncpy(nacp->title[(byte_t)mTitle[i].language].name, mTitle[i].name.c_str(), nacp::kNameLength);
		strncpy(nacp->title[(byte_t)mTitle[i].language].publisher, mTitle[i].publisher.c_str(), nacp::kPublisherLength);
	}

	uint32_t supported_langs = 0;
	for (size_t i = 0; i < mSupportedLanguage.size(); i++)
	{
		supported_langs |= _BIT(mSupportedLanguage[i]);
	}
	nacp->supported_language_flag = supported_langs;

	strncpy(nacp->isbn, mIsbn.c_str(), nacp::kIsbnLength);
	strncpy(nacp->display_version, mDisplayVersion.c_str(), nacp::kDisplayVersionLength);
	strncpy(nacp->application_error_code_category, mApplicationErrorCodeCategory.c_str(), nacp::kApplicationErrorCodeCategoryLength);
	strncpy(nacp->bcat_passphrase, mBcatPassphase.c_str(), nacp::kBcatPassphraseLength);

	// bitfields
	uint32_t attribute_flag = 0;
	for (size_t i = 0; i < mAttribute.size(); i++)
	{
		attribute_flag |= _BIT(mSupportedLanguage[i]);
	}
	nacp->attribute_flag = attribute_flag;

	uint32_t parental_control_flag = 0;
	for (size_t i = 0; i < mParentalControl.size(); i++)
	{
		parental_control_flag |= _BIT(mParentalControl[i]);
	}
	nacp->parental_control_flag = parental_control_flag;

	byte_t startup_user_option = 0;
	for (size_t i = 0; i < mStartupUserAccountOption.size(); i++)
	{
		startup_user_option |= _BIT(mStartupUserAccountOption[i]);
	}
	nacp->startup_user_account_option = startup_user_option;

	byte_t repair_flag = 0;
	for (size_t i = 0; i < mRepair.size(); i++)
	{
		repair_flag |= _BIT(mRepair[i]);
	}
	nacp->repair_flag = repair_flag;

	byte_t required_network_service_license_on_launch_flag = 0;
	for (size_t i = 0; i < mRequiredNetworkServiceLicenseOnLaunch.size(); i++)
	{
		required_network_service_license_on_launch_flag |= _BIT(mRequiredNetworkServiceLicenseOnLaunch[i]);
	}
	nacp->required_network_service_license_on_launch_flag = required_network_service_license_on_launch_flag;


	// enum type casts
	nacp->startup_user_account = (byte_t)mStartupUserAccount;
	nacp->user_account_switch_lock = (byte_t)mUserAccountSwitchLock;
	nacp->add_on_content_registration_type = (byte_t)mAddOnContentRegistrationType;
	nacp->screenshot = (byte_t)mScreenshot;
	nacp->video_capture = (byte_t)mVideoCapture;
	nacp->data_loss_confirmation = (byte_t)mDataLossConfirmation;
	nacp->play_log_policy = (byte_t)mPlayLogPolicy;
	nacp->logo_type = (byte_t)mLogoType;
	nacp->logo_handling = (byte_t)mLogoHandling;
	nacp->runtime_add_on_content_install = (byte_t)mRuntimeAddOnContentInstall;
	nacp->runtime_parameter_delivery = (byte_t)mRuntimeParameterDelivery;
	nacp->crash_report = (byte_t)mCrashReport;
	nacp->hdcp = (byte_t)mHdcp;
	nacp->play_log_query_capability = (byte_t)mPlayLogQueryCapability;
	

	// misc params
	nacp->presence_group_id = mPresenceGroupId;
	memset(nacp->rating_age, nacp::kUnusedAgeRating, nacp::kRatingAgeCount); // clear ratings
	for (size_t i = 0; i < mRatingAge.size(); i++)
	{
		nacp->rating_age[(byte_t)mRatingAge[i].organisation] = mRatingAge[i].age;
	}
	nacp->add_on_content_base_id = mAddOnContentBaseId;
	nacp->save_data_owner_id = mSaveDatawOwnerId;
	for (size_t i = 0; i < mLocalCommunicationId.size() && i < nacp::kLocalCommunicationIdCount; i++)
	{
		nacp->local_communication_id[i] = mLocalCommunicationId[i];
	}
	nacp->seed_for_pseudo_device_id = mSeedForPsuedoDeviceId;
	for (size_t i = 0; i < mPlayLogQueryableApplicationId.size() && i < nacp::kPlayLogQueryableApplicationIdCount; i++)
	{
		nacp->play_log_queryable_application_id[i] = mPlayLogQueryableApplicationId[i];
	}
	nacp->cache_storage_index_max = mCacheStorageIndexMax;
	nacp->program_index = mProgramIndex;

	// sizes
	nacp->user_account_save_data_size = mUserAccountSaveDataSize.size;
	nacp->user_account_save_data_journal_size = mUserAccountSaveDataSize.journal_size;
	nacp->device_save_data_size = mDeviceSaveDataSize.size;
	nacp->device_save_data_journal_size = mDeviceSaveDataSize.journal_size;
	nacp->bcat_delivery_cache_storage_size = mBcatDeliveryCacheStorageSize;
	nacp->user_account_save_data_size_max = mUserAccountSaveDataMax.size;
	nacp->user_account_save_data_journal_size_max = mUserAccountSaveDataMax.journal_size;
	nacp->device_save_data_size_max = mDeviceSaveDataMax.size;
	nacp->device_save_data_journal_size_max = mDeviceSaveDataMax.journal_size;
	nacp->temporary_storage_size = 	mTemporaryStorageSize;
	nacp->cache_storage_size = mCacheStorageSize.size;
	nacp->cache_storage_journal_size = mCacheStorageSize.journal_size;
	nacp->cache_storage_data_and_journal_size_max = mCacheStorageDataAndJournalSizeMax;

	// jit configuration
	uint64_t jit_config_flag = 0;
	if (mJitConfiguration.is_enabled)
		jit_config_flag |= _BIT(nacp::JitConfigurationFlag::Enabled);
	nacp->jit_configuration.jit_configuration_flag =  jit_config_flag;
	nacp->jit_configuration.memory_size = mJitConfiguration.memory_size;

	// neighbor detection client configuration
	serialiseGroupConfig(mNeighborDetectionClientConfiguration.send_data_configuration, nacp->neighbour_detection_client_configuration.send_group_configuration);
	for (size_t i = 0; i < nacp::kReceivableGroupConfigurationCount; i++)
	{
		serialiseGroupConfig(mNeighborDetectionClientConfiguration.receivable_data_configuration[i], nacp->neighbour_detection_client_configuration.receivable_group_configuration[i]);
	}
}

void nn::hac::ApplicationControlProperty::fromBytes(const byte_t* bytes, size_t len)
{
	if (len < sizeof(nn::hac::sApplicationControlProperty))
	{
		throw fnd::Exception(kModuleName, "NACP too small");
	}

	clear();

	mRawBinary.alloc(sizeof(nn::hac::sApplicationControlProperty));
	memcpy(mRawBinary.data(), bytes, mRawBinary.size());

	const sApplicationControlProperty* nacp = (const sApplicationControlProperty*)mRawBinary.data();

	// strings
	for (size_t i = 0; i < nacp::kMaxLanguageCount; i++)
	{
		if (_HAS_BIT(nacp->supported_language_flag.get(), i))
		{
			mSupportedLanguage.addElement(nacp::Language(i));
		}
		if (nacp->title[i].name[0] != '\0' && nacp->title[i].publisher[0] != '\0')
		{
			mTitle.addElement({ nacp::Language(i), std::string(nacp->title[i].name, _MIN(strlen(nacp->title[i].name), nacp::kNameLength)), std::string(nacp->title[i].publisher, _MIN(strlen(nacp->title[i].publisher), nacp::kPublisherLength)) });
		}
	}

	if (nacp->isbn[0] != 0)
		mIsbn = std::string(nacp->isbn, _MIN(strlen(nacp->isbn), nacp::kIsbnLength));
	if (nacp->display_version[0] != 0)
		mDisplayVersion = std::string(nacp->display_version, _MIN(strlen(nacp->display_version), nacp::kDisplayVersionLength));
	if (nacp->application_error_code_category[0] != 0)
		mApplicationErrorCodeCategory = std::string(nacp->application_error_code_category, _MIN(strlen(nacp->application_error_code_category), nacp::kApplicationErrorCodeCategoryLength));
	if (nacp->bcat_passphrase[0] != 0)
		mBcatPassphase = std::string(nacp->bcat_passphrase, _MIN(strlen(nacp->bcat_passphrase), nacp::kBcatPassphraseLength));

	// bitfield values
	for (size_t i = 0; i < sizeof(uint32_t) * 8; i++)
	{
		if (_HAS_BIT(nacp->attribute_flag.get(), i))
		{
			mAttribute.addElement(nacp::AttributeFlag(i));
		}
	}
	for (size_t i = 0; i < sizeof(uint32_t) * 8; i++)
	{
		if (_HAS_BIT(nacp->parental_control_flag.get(), i))
		{
			mParentalControl.addElement(nacp::ParentalControlFlag(i));
		}
	}
	for (size_t i = 0; i < sizeof(byte_t) * 8; i++)
	{
		if (_HAS_BIT(nacp->startup_user_account_option, i))
		{
			mStartupUserAccountOption.addElement(nacp::StartupUserAccountOptionFlag(i));
		}
	}
	for (size_t i = 0; i < sizeof(byte_t) * 8; i++)
	{
		if (_HAS_BIT(nacp->repair_flag, i))
		{
			mRepair.addElement(nacp::RepairFlag(i));
		}
	}

	for (size_t i = 0; i < sizeof(byte_t) * 8; i++)
	{
		if (_HAS_BIT(nacp->required_network_service_license_on_launch_flag, i))
		{
			mRequiredNetworkServiceLicenseOnLaunch.addElement(nacp::RequiredNetworkServiceLicenseOnLaunchFlag(i));
		}
	}
	// enum type casts
	mStartupUserAccount = nacp::StartupUserAccount(nacp->startup_user_account);
	mUserAccountSwitchLock = nacp::UserAccountSwitchLock(nacp->user_account_switch_lock);
	mAddOnContentRegistrationType = nacp::AddOnContentRegistrationType(nacp->add_on_content_registration_type);
	mScreenshot = nacp::Screenshot(nacp->screenshot);
	mVideoCapture = nacp::VideoCapture(nacp->video_capture);
	mDataLossConfirmation = nacp::DataLossConfirmation(nacp->data_loss_confirmation);
	mPlayLogPolicy = nacp::PlayLogPolicy(nacp->play_log_policy);
	mLogoType = nacp::LogoType(nacp->logo_type);
	mLogoHandling = nacp::LogoHandling(nacp->logo_handling);
	mRuntimeAddOnContentInstall = nacp::RuntimeAddOnContentInstall(nacp->runtime_add_on_content_install);
	mRuntimeParameterDelivery = nacp::RuntimeParameterDelivery(nacp->runtime_parameter_delivery);
	mCrashReport = nacp::CrashReport(nacp->crash_report);
	mHdcp = nacp::Hdcp(nacp->hdcp);
	mPlayLogQueryCapability = nacp::PlayLogQueryCapability(nacp->play_log_query_capability);

	// misc params
	mPresenceGroupId = nacp->presence_group_id.get();
	for (size_t i = 0; i < nacp::kRatingAgeCount; i++)
	{
		if (nacp->rating_age[i] != nacp::kUnusedAgeRating)
			mRatingAge.addElement({nacp::Organisation(i), nacp->rating_age[i]});
	}
	mAddOnContentBaseId = nacp->add_on_content_base_id.get();
	mSaveDatawOwnerId = nacp->save_data_owner_id.get();
	for (size_t i = 0; i < nacp::kLocalCommunicationIdCount; i++)
	{
		if (nacp->local_communication_id[i].get() != 0)
			mLocalCommunicationId.addElement(nacp->local_communication_id[i].get());
	}
	mSeedForPsuedoDeviceId = nacp->seed_for_pseudo_device_id.get();
	for (size_t i = 0; i < nacp::kPlayLogQueryableApplicationIdCount; i++)
	{
		if (nacp->play_log_queryable_application_id[i].get() != 0)
			mPlayLogQueryableApplicationId.addElement(nacp->play_log_queryable_application_id[i].get());
	}
	mCacheStorageIndexMax = nacp->cache_storage_index_max.get();
	mProgramIndex = nacp->program_index;

	// sizes
	mUserAccountSaveDataSize.size = (int64_t)nacp->user_account_save_data_size.get();
	mUserAccountSaveDataSize.journal_size = (int64_t)nacp->user_account_save_data_journal_size.get();
	mDeviceSaveDataSize.size = (int64_t)nacp->device_save_data_size.get();
	mDeviceSaveDataSize.journal_size = (int64_t)nacp->device_save_data_journal_size.get();
	mBcatDeliveryCacheStorageSize = (int64_t)nacp->bcat_delivery_cache_storage_size.get();
	mUserAccountSaveDataMax.size = (int64_t)nacp->user_account_save_data_size_max.get();
	mUserAccountSaveDataMax.journal_size = (int64_t)nacp->user_account_save_data_journal_size_max.get();
	mDeviceSaveDataMax.size = (int64_t)nacp->device_save_data_size_max.get();
	mDeviceSaveDataMax.journal_size = (int64_t)nacp->device_save_data_journal_size_max.get();
	mTemporaryStorageSize = (int64_t)nacp->temporary_storage_size.get();
	mCacheStorageSize.size = (int64_t)nacp->cache_storage_size.get();
	mCacheStorageSize.journal_size = (int64_t)nacp->cache_storage_journal_size.get();
	mCacheStorageDataAndJournalSizeMax = (int64_t)nacp->cache_storage_data_and_journal_size_max.get();

	// jit configuration
	mJitConfiguration.is_enabled = _HAS_BIT(nacp->jit_configuration.jit_configuration_flag.get(), nacp::JitConfigurationFlag::Enabled);
	mJitConfiguration.memory_size = nacp->jit_configuration.memory_size.get();

	// neighbor detection client configuration
	parseGroupConfig(nacp->neighbour_detection_client_configuration.send_group_configuration, mNeighborDetectionClientConfiguration.send_data_configuration);
	for (size_t i = 0; i < nacp::kReceivableGroupConfigurationCount; i++)
	{
		parseGroupConfig(nacp->neighbour_detection_client_configuration.receivable_group_configuration[i], mNeighborDetectionClientConfiguration.receivable_data_configuration[i]);
	}
}

const fnd::Vec<byte_t>& nn::hac::ApplicationControlProperty::getBytes() const
{
	return mRawBinary;
}

void nn::hac::ApplicationControlProperty::clear()
{
	mRawBinary.clear();
	mTitle.clear();
	mIsbn.clear();
	mStartupUserAccount = nacp::StartupUserAccount::None;
	mUserAccountSwitchLock = nacp::UserAccountSwitchLock::Disable;
	mAddOnContentRegistrationType = nacp::AddOnContentRegistrationType::AllOnLaunch;
	mAttribute.clear();
	mSupportedLanguage.clear();
	mParentalControl.clear();
	mScreenshot = nacp::Screenshot::Allow;
	mVideoCapture = nacp::VideoCapture::Disable;
	mDataLossConfirmation = nacp::DataLossConfirmation::None;
	mPlayLogPolicy = nacp::PlayLogPolicy::All;
	mPresenceGroupId = 0;
	mRatingAge.clear();
	mDisplayVersion.clear();
	mAddOnContentBaseId = 0;
	mSaveDatawOwnerId = 0;
	mUserAccountSaveDataSize = {0, 0};
	mDeviceSaveDataSize = {0, 0};
	mBcatDeliveryCacheStorageSize = 0;
	mApplicationErrorCodeCategory.clear();
	mLocalCommunicationId.clear();
	mLogoType = nacp::LogoType::Nintendo;
	mLogoHandling = nacp::LogoHandling::Auto;
	mRuntimeAddOnContentInstall = nacp::RuntimeAddOnContentInstall::Deny;
	mCrashReport = nacp::CrashReport::Deny;
	mHdcp = nacp::Hdcp::None;
	mSeedForPsuedoDeviceId = 0;
	mBcatPassphase.clear();
	mStartupUserAccountOption.clear();
	mUserAccountSaveDataMax = {0, 0};
	mDeviceSaveDataMax = {0, 0};
	mTemporaryStorageSize = 0;
	mCacheStorageSize = {0, 0};
	mCacheStorageDataAndJournalSizeMax = 0;
	mCacheStorageIndexMax = 0;
	mPlayLogQueryableApplicationId.clear();
	mPlayLogQueryCapability = nacp::PlayLogQueryCapability::None;
	mRepair.clear();
	mProgramIndex = 0;
	mRequiredNetworkServiceLicenseOnLaunch.clear();
	mNeighborDetectionClientConfiguration = sNeighborDetectionClientConfiguration();
	mJitConfiguration = sJitConfiguration();
}

const fnd::List<nn::hac::ApplicationControlProperty::sTitle>& nn::hac::ApplicationControlProperty::getTitle() const
{
	return mTitle;
}

void nn::hac::ApplicationControlProperty::setTitle(const fnd::List<sTitle>& title)
{
	mTitle = title;
}

const std::string& nn::hac::ApplicationControlProperty::getIsbn() const
{
	return mIsbn;
}

void nn::hac::ApplicationControlProperty::setIsbn(const std::string& isbn)
{
	mIsbn = isbn;
}

nn::hac::nacp::StartupUserAccount nn::hac::ApplicationControlProperty::getStartupUserAccount() const
{
	return mStartupUserAccount;
}

void nn::hac::ApplicationControlProperty::setStartupUserAccount(nacp::StartupUserAccount var)
{
	mStartupUserAccount = var;
}

nn::hac::nacp::UserAccountSwitchLock nn::hac::ApplicationControlProperty::getUserAccountSwitchLock() const
{
	return mUserAccountSwitchLock;
}

void nn::hac::ApplicationControlProperty::setUserAccountSwitchLock(nacp::UserAccountSwitchLock var)
{
	mUserAccountSwitchLock = var;
}

nn::hac::nacp::AddOnContentRegistrationType nn::hac::ApplicationControlProperty::getAddOnContentRegistrationType() const
{
	return mAddOnContentRegistrationType;
}

void nn::hac::ApplicationControlProperty::setAddOnContentRegistrationType(nacp::AddOnContentRegistrationType var)
{
	mAddOnContentRegistrationType = var;
}

const fnd::List<nn::hac::nacp::AttributeFlag>& nn::hac::ApplicationControlProperty::getAttribute() const
{
	return mAttribute;
}

void nn::hac::ApplicationControlProperty::setAttribute(const fnd::List<nacp::AttributeFlag>& var)
{
	mAttribute = var;
}

const fnd::List<nn::hac::nacp::Language>& nn::hac::ApplicationControlProperty::getSupportedLanguage() const
{
	return mSupportedLanguage;
}

void nn::hac::ApplicationControlProperty::setSupportedLanguage(const fnd::List<nacp::Language>& var)
{
	mSupportedLanguage = var;
}

const fnd::List<nn::hac::nacp::ParentalControlFlag>& nn::hac::ApplicationControlProperty::getParentalControl() const
{
	return mParentalControl;
}

void nn::hac::ApplicationControlProperty::setParentalControl(const fnd::List<nacp::ParentalControlFlag>& var)
{
	mParentalControl = var;
}

nn::hac::nacp::Screenshot nn::hac::ApplicationControlProperty::getScreenshot() const
{
	return mScreenshot;
}

void nn::hac::ApplicationControlProperty::setScreenshot(nacp::Screenshot var)
{
	mScreenshot = var;
}

nn::hac::nacp::VideoCapture nn::hac::ApplicationControlProperty::getVideoCapture() const
{
	return mVideoCapture;
}

void nn::hac::ApplicationControlProperty::setVideoCapture(nacp::VideoCapture var)
{
	mVideoCapture = var;
}

nn::hac::nacp::DataLossConfirmation nn::hac::ApplicationControlProperty::getDataLossConfirmation() const
{
	return mDataLossConfirmation;
}

void nn::hac::ApplicationControlProperty::setDataLossConfirmation(nacp::DataLossConfirmation var)
{
	mDataLossConfirmation = var;
}

nn::hac::nacp::PlayLogPolicy nn::hac::ApplicationControlProperty::getPlayLogPolicy() const
{
	return mPlayLogPolicy;
}

void nn::hac::ApplicationControlProperty::setPlayLogPolicy(nacp::PlayLogPolicy var)
{
	mPlayLogPolicy = var;
}

uint64_t nn::hac::ApplicationControlProperty::getPresenceGroupId() const
{
	return mPresenceGroupId;
}

void nn::hac::ApplicationControlProperty::setPresenceGroupId(uint64_t var)
{
	mPresenceGroupId = var;
}

const fnd::List<nn::hac::ApplicationControlProperty::sRating>& nn::hac::ApplicationControlProperty::getRatingAge() const
{
	return mRatingAge;
}

void nn::hac::ApplicationControlProperty::setRatingAge(const fnd::List<sRating>& var)
{
	mRatingAge = var;
}

const std::string& nn::hac::ApplicationControlProperty::getDisplayVersion() const
{
	return mDisplayVersion;
}

void nn::hac::ApplicationControlProperty::setDisplayVersion(const std::string& var)
{
	mDisplayVersion = var;
}

uint64_t nn::hac::ApplicationControlProperty::getAddOnContentBaseId() const
{
	return mAddOnContentBaseId;
}

void nn::hac::ApplicationControlProperty::setAddOnContentBaseId(uint64_t var)
{
	mAddOnContentBaseId = var;
}

uint64_t nn::hac::ApplicationControlProperty::getSaveDatawOwnerId() const
{
	return mSaveDatawOwnerId;
}

void nn::hac::ApplicationControlProperty::setSaveDatawOwnerId(uint64_t var)
{
	mSaveDatawOwnerId = var;
}

const nn::hac::ApplicationControlProperty::sStorageSize& nn::hac::ApplicationControlProperty::getUserAccountSaveDataSize() const
{
	return mUserAccountSaveDataSize;
}

void nn::hac::ApplicationControlProperty::setUserAccountSaveDataSize(const sStorageSize& var)
{
	mUserAccountSaveDataSize = var;
}

const nn::hac::ApplicationControlProperty::sStorageSize& nn::hac::ApplicationControlProperty::getDeviceSaveDataSize() const
{
	return mDeviceSaveDataSize;
}

void nn::hac::ApplicationControlProperty::setDeviceSaveDataSize(const sStorageSize& var)
{
	mDeviceSaveDataSize = var;
}

int64_t nn::hac::ApplicationControlProperty::getBcatDeliveryCacheStorageSize() const
{
	return mBcatDeliveryCacheStorageSize;
}

void nn::hac::ApplicationControlProperty::setBcatDeliveryCacheStorageSize(int64_t var)
{
	mBcatDeliveryCacheStorageSize = var;
}

const std::string& nn::hac::ApplicationControlProperty::getApplicationErrorCodeCategory() const
{
	return mApplicationErrorCodeCategory;
}

void nn::hac::ApplicationControlProperty::setApplicationErrorCodeCategory(const std::string& var)
{
	mApplicationErrorCodeCategory = var;
}

const fnd::List<uint64_t>& nn::hac::ApplicationControlProperty::getLocalCommunicationId() const
{
	return mLocalCommunicationId;
}

void nn::hac::ApplicationControlProperty::setLocalCommunicationId(const fnd::List<uint64_t>& var)
{
	mLocalCommunicationId = var;
}

nn::hac::nacp::LogoType nn::hac::ApplicationControlProperty::getLogoType() const
{
	return mLogoType;
}

void nn::hac::ApplicationControlProperty::setLogoType(nacp::LogoType var)
{
	mLogoType = var;
}

nn::hac::nacp::LogoHandling nn::hac::ApplicationControlProperty::getLogoHandling() const
{
	return mLogoHandling;
}

void nn::hac::ApplicationControlProperty::setLogoHandling(nacp::LogoHandling var)
{
	mLogoHandling = var;
}

nn::hac::nacp::RuntimeAddOnContentInstall nn::hac::ApplicationControlProperty::getRuntimeAddOnContentInstall() const
{
	return mRuntimeAddOnContentInstall;
}

void nn::hac::ApplicationControlProperty::setRuntimeAddOnContentInstall(nacp::RuntimeAddOnContentInstall var)
{
	mRuntimeAddOnContentInstall = var;
}

nn::hac::nacp::RuntimeParameterDelivery nn::hac::ApplicationControlProperty::getRuntimeParameterDelivery() const
{
	return mRuntimeParameterDelivery;
}

void nn::hac::ApplicationControlProperty::setRuntimeParameterDelivery(nacp::RuntimeParameterDelivery var)
{
	mRuntimeParameterDelivery = var;
}

nn::hac::nacp::CrashReport nn::hac::ApplicationControlProperty::getCrashReport() const
{
	return mCrashReport;
}

void nn::hac::ApplicationControlProperty::setCrashReport(nacp::CrashReport var)
{
	mCrashReport = var;
}

nn::hac::nacp::Hdcp nn::hac::ApplicationControlProperty::getHdcp() const
{
	return mHdcp;
}

void nn::hac::ApplicationControlProperty::setHdcp(nacp::Hdcp var)
{
	mHdcp = var;
}

uint64_t nn::hac::ApplicationControlProperty::getSeedForPsuedoDeviceId() const
{
	return mSeedForPsuedoDeviceId;
}

void nn::hac::ApplicationControlProperty::setSeedForPsuedoDeviceId(uint64_t var)
{
	mSeedForPsuedoDeviceId = var;
}

const std::string& nn::hac::ApplicationControlProperty::getBcatPassphase() const
{
	return mBcatPassphase;
}

void nn::hac::ApplicationControlProperty::setBcatPassphase(const std::string& var)
{
	mBcatPassphase = var;
}

const fnd::List<nn::hac::nacp::StartupUserAccountOptionFlag>& nn::hac::ApplicationControlProperty::getStartupUserAccountOption() const
{
	return mStartupUserAccountOption;
}

void nn::hac::ApplicationControlProperty::setStartupUserAccountOption(const fnd::List<nacp::StartupUserAccountOptionFlag>& var)
{
	mStartupUserAccountOption = var;
}


const nn::hac::ApplicationControlProperty::sStorageSize& nn::hac::ApplicationControlProperty::getUserAccountSaveDataMax() const
{
	return mUserAccountSaveDataMax;
}

void nn::hac::ApplicationControlProperty::setUserAccountSaveDataMax(const sStorageSize& var)
{
	mUserAccountSaveDataMax = var;
}

const nn::hac::ApplicationControlProperty::sStorageSize& nn::hac::ApplicationControlProperty::getDeviceSaveDataMax() const
{
	return mDeviceSaveDataMax;
}

void nn::hac::ApplicationControlProperty::setDeviceSaveDataMax(const sStorageSize& var)
{
	mDeviceSaveDataMax = var;
}

int64_t nn::hac::ApplicationControlProperty::getTemporaryStorageSize() const
{
	return mTemporaryStorageSize;
}

void nn::hac::ApplicationControlProperty::setTemporaryStorageSize(int64_t var)
{
	mTemporaryStorageSize = var;
}

const nn::hac::ApplicationControlProperty::sStorageSize& nn::hac::ApplicationControlProperty::getCacheStorageSize() const
{
	return mCacheStorageSize;
}

void nn::hac::ApplicationControlProperty::setCacheStorageSize(const sStorageSize& var)
{
	mCacheStorageSize = var;
}

int64_t nn::hac::ApplicationControlProperty::getCacheStorageDataAndJournalSizeMax() const
{
	return mCacheStorageDataAndJournalSizeMax;
}

void nn::hac::ApplicationControlProperty::setCacheStorageDataAndJournalSizeMax(int64_t var)
{
	mCacheStorageDataAndJournalSizeMax = var;
}

uint16_t nn::hac::ApplicationControlProperty::getCacheStorageIndexMax() const
{
	return mCacheStorageIndexMax;
}

void nn::hac::ApplicationControlProperty::setCacheStorageIndexMax(uint16_t var)
{
	mCacheStorageIndexMax = var;
}

const fnd::List<uint64_t>& nn::hac::ApplicationControlProperty::getPlayLogQueryableApplicationId() const
{
	return mPlayLogQueryableApplicationId;
}

void nn::hac::ApplicationControlProperty::setPlayLogQueryableApplicationId(const fnd::List<uint64_t>& var)
{
	mPlayLogQueryableApplicationId = var;
}

nn::hac::nacp::PlayLogQueryCapability nn::hac::ApplicationControlProperty::getPlayLogQueryCapability() const
{
	return mPlayLogQueryCapability;
}

void nn::hac::ApplicationControlProperty::setPlayLogQueryCapability(nacp::PlayLogQueryCapability var)
{
	mPlayLogQueryCapability = var;
}

const fnd::List<nn::hac::nacp::RepairFlag>& nn::hac::ApplicationControlProperty::getRepair() const
{
	return mRepair;
}

void nn::hac::ApplicationControlProperty::setRepair(const fnd::List<nacp::RepairFlag>& var)
{
	mRepair = var;
}

byte_t nn::hac::ApplicationControlProperty::getProgramIndex() const
{
	return mProgramIndex;
}

void nn::hac::ApplicationControlProperty::setProgramIndex(byte_t var)
{
	mProgramIndex = var;
}

const fnd::List<nn::hac::nacp::RequiredNetworkServiceLicenseOnLaunchFlag>& nn::hac::ApplicationControlProperty::getRequiredNetworkServiceLicenseOnLaunch() const
{
	return mRequiredNetworkServiceLicenseOnLaunch;
}

void nn::hac::ApplicationControlProperty::setRequiredNetworkServiceLicenseOnLaunch(const fnd::List<nacp::RequiredNetworkServiceLicenseOnLaunchFlag>& var)
{
	mRequiredNetworkServiceLicenseOnLaunch = var;
}

const nn::hac::ApplicationControlProperty::sNeighborDetectionClientConfiguration& nn::hac::ApplicationControlProperty::getNeighborDetectionClientConfiguration() const
{
	return mNeighborDetectionClientConfiguration;
}

void nn::hac::ApplicationControlProperty::setNeighborDetectionClientConfiguration(const sNeighborDetectionClientConfiguration& var)
{
	mNeighborDetectionClientConfiguration = var;
}

const nn::hac::ApplicationControlProperty::sJitConfiguration& nn::hac::ApplicationControlProperty::getJitConfiguration() const
{
	return mJitConfiguration;
}

void nn::hac::ApplicationControlProperty::setJitConfiguration(const sJitConfiguration& var)
{
	mJitConfiguration = var;
}

void nn::hac::ApplicationControlProperty::serialiseGroupConfig(const sNeighborDetectionClientConfiguration::sGroupConfiguration& logical, sApplicationControlProperty::sNeighborDetectionClientConfiguration::sGroupConfiguration& serialised)
{
	if (logical.isNull())
	{
		memset(&serialised, 0, sizeof(sApplicationControlProperty::sNeighborDetectionClientConfiguration::sGroupConfiguration));
		return;
	}

	serialised.group_id = logical.group_id;
	memcpy(serialised.key, logical.key, nacp::kNeighborDetectionGroupConfigurationKeyLength);
}

void nn::hac::ApplicationControlProperty::parseGroupConfig(const sApplicationControlProperty::sNeighborDetectionClientConfiguration::sGroupConfiguration& serialised, sNeighborDetectionClientConfiguration::sGroupConfiguration& logical)
{
	logical.group_id = serialised.group_id.get();
	memcpy(logical.key, serialised.key, nacp::kNeighborDetectionGroupConfigurationKeyLength);
}