#include <nn/hac/FileSystemAccessUtil.h>
#include <sstream>
#include <iomanip>

std::string nn::hac::FileSystemAccessUtil::getFsaRightAsString(nn::hac::fac::FsAccessFlag flag)
{
	std::stringstream ss;

	switch(flag)
	{
	case (nn::hac::fac::FSA_APPLICATION_INFO):
		ss << "ApplicationInfo";
		break;
	case (nn::hac::fac::FSA_BOOT_MODE_CONTROL):
		ss << "BootModeControl";
		break;
	case (nn::hac::fac::FSA_CALIBRATION):
		ss << "Calibration";
		break;
	case (nn::hac::fac::FSA_SYSTEM_SAVE_DATA):
		ss << "SystemSaveData";
		break;
	case (nn::hac::fac::FSA_GAME_CARD):
		ss << "GameCard";
		break;
	case (nn::hac::fac::FSA_SAVE_DATA_BACKUP):
		ss << "SaveDataBackUp";
		break;
	case (nn::hac::fac::FSA_SAVE_DATA_MANAGEMENT):
		ss << "SaveDataManagement";
		break;
	case (nn::hac::fac::FSA_BIS_ALL_RAW):
		ss << "BisAllRaw";
		break;
	case (nn::hac::fac::FSA_GAME_CARD_RAW):
		ss << "GameCardRaw";
		break;
	case (nn::hac::fac::FSA_GAME_CARD_PRIVATE):
		ss << "GameCardPrivate";
		break;
	case (nn::hac::fac::FSA_SET_TIME):
		ss << "SetTime";
		break;
	case (nn::hac::fac::FSA_CONTENT_MANAGER):
		ss << "ContentManager";
		break;
	case (nn::hac::fac::FSA_IMAGE_MANAGER):
		ss << "ImageManager";
		break;
	case (nn::hac::fac::FSA_CREATE_SAVE_DATA):
		ss << "CreateSaveData";
		break;
	case (nn::hac::fac::FSA_SYSTEM_SAVE_DATA_MANAGEMENT):
		ss << "SystemSaveDataManagement";
		break;
	case (nn::hac::fac::FSA_BIS_FILE_SYSTEM):
		ss << "BisFileSystem";
		break;
	case (nn::hac::fac::FSA_SYSTEM_UPDATE):
		ss << "SystemUpdate";
		break;
	case (nn::hac::fac::FSA_SAVE_DATA_META):
		ss << "SaveDataMeta";
		break;
	case (nn::hac::fac::FSA_DEVICE_SAVE_CONTROL):
		ss << "DeviceSaveData";
		break;
	case (nn::hac::fac::FSA_SETTINGS_CONTROL):
		ss << "SettingsControl";
		break;
	case (nn::hac::fac::FSA_SYSTEM_DATA):
		ss << "SystemData";
		break;
	case (nn::hac::fac::FSA_SD_CARD):
		ss << "SdCard";
		break;
	case (nn::hac::fac::FSA_HOST):
		ss << "Host";
		break;
	case (nn::hac::fac::FSA_FILL_BIS):
		ss << "FillBis";
		break;
	case (nn::hac::fac::FSA_CORRUPT_SAVE_DATA):
		ss << "CorruptSaveData";
		break;
	case (nn::hac::fac::FSA_SAVE_DATA_FOR_DEBUG):
		ss << "SaveDataForDebug";
		break;
	case (nn::hac::fac::FSA_FORMAT_SD_CARD):
		ss << "FormateSdCard";
		break;
	case (nn::hac::fac::FSA_GET_RIGHTS_ID):
		ss << "GetRightsId";
		break;
	case (nn::hac::fac::FSA_REGISTER_EXTERNAL_KEY):
		ss << "RegisterExternalKey";
		break;
	case (nn::hac::fac::FSA_REGISTER_UPDATE_PARTITION):
		ss << "RegisterUpdatePartition";
		break;
	case (nn::hac::fac::FSA_SAVE_DATA_TRANSFER):
		ss << "SaveDataTransfer";
		break;
	case (nn::hac::fac::FSA_DEVICE_DETECTION):
		ss << "DeviceDetection";
		break;
	case (nn::hac::fac::FSA_ACCESS_FAILURE_RESOLUTION):
		ss << "AccessFailureResolution";
		break;
	case (nn::hac::fac::FSA_SAVE_DATA_TRANSFER_VERSION_2):
		ss << "SaveDataTransferVersion2";
		break;
	case (nn::hac::fac::FSA_REGISTER_PROGRAM_INDEX_MAP_INFO):
		ss << "RegisterProgramIndexMapInfo";
		break;
	case (nn::hac::fac::FSA_CREATE_OWN_SAVE_DATA):
		ss << "CreateOwnSaveData";
		break;
	case (nn::hac::fac::FSA_DEBUG):
		ss << "Debug";
		break;
	case (nn::hac::fac::FSA_FULL_PERMISSION):
		ss << "FullPermission";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)flag;
		break;
	}

	return ss.str();
}

std::string nn::hac::FileSystemAccessUtil::getSaveDataOwnerAccessModeAsString(nn::hac::fac::SaveDataOwnerIdAccessType type)
{
	std::stringstream ss;

	switch(type)
	{
	case (nn::hac::fac::SDO_READ):
		ss << "Read";
		break;
	case (nn::hac::fac::SDO_WRITE):
		ss << "Write";
		break;
	case (nn::hac::fac::SDO_READWRITE):
		ss << "ReadWrite";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)type;
		break;
	}

	return ss.str();
}