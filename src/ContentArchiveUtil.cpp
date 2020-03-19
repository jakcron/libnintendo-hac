#include <nn/hac/ContentArchiveUtil.h>
#include <sstream>
#include <iomanip>

void nn::hac::ContentArchiveUtil::decryptContentArchiveHeader(const byte_t* src, byte_t* dst, const fnd::aes::sAesXts128Key& key)
{
	byte_t tweak[fnd::aes::kAesBlockSize];

	// decrypt main header
	byte_t raw_hdr[nn::hac::nca::kSectorSize];
	fnd::aes::AesXtsMakeTweak(tweak, 1);
	fnd::aes::AesXtsDecryptSector(src + sectorToOffset(1), nn::hac::nca::kSectorSize, key.key[0], key.key[1], tweak, raw_hdr);

	bool useNca2SectorIndex = ((nn::hac::sContentArchiveHeader*)(raw_hdr))->st_magic.get() == nn::hac::nca::kNca2StructMagic;

	// decrypt whole header
	for (size_t i = 0; i < nn::hac::nca::kHeaderSectorNum; i++)
	{
		fnd::aes::AesXtsMakeTweak(tweak, (i > 1 && useNca2SectorIndex)? 0 : i);
		fnd::aes::AesXtsDecryptSector(src + sectorToOffset(i), nn::hac::nca::kSectorSize, key.key[0], key.key[1], tweak, dst + sectorToOffset(i));
	}
}

byte_t nn::hac::ContentArchiveUtil::getMasterKeyRevisionFromKeyGeneration(byte_t key_generation)
{
	byte_t masterkey_rev;

	switch (key_generation)
	{
		case(0):
		case(1):
			masterkey_rev = 0;
			break;
		case(2):
			masterkey_rev = 1;
			break;
		case(3):
			masterkey_rev = 2;
			break;
		case(4):
			masterkey_rev = 3;
			break;
		case(5):
			masterkey_rev = 4;
			break;
		default:
			masterkey_rev = key_generation - 1;
	}

	return masterkey_rev;
}

void nn::hac::ContentArchiveUtil::getNcaPartitionAesCtr(const nn::hac::sContentArchiveFsHeader* hdr, byte_t* aes_ctr)
{
	getNcaPartitionAesCtr(hdr->generation.get(), hdr->secure_value.get(), aes_ctr);
}

void nn::hac::ContentArchiveUtil::getNcaPartitionAesCtr(uint32_t generation, uint32_t secure_value, byte_t* aes_ctr)
{
	/*
	for (size_t i = 0; i < 8; i++)
	{
		ctr[7-i] = hdr->aes_ctr_upper[i];
		ctr[15-i] = 0;
	}
	*/
	// hdr->aes_ctr_upper = 00 01 02 03 04 05 06 07
	// output             = 07 06 05 04 03 02 01 00 
	// generation = 03020100, secure_value = 07060504
	be_uint32_t* aes_ctr_words = (be_uint32_t*)aes_ctr;
	aes_ctr_words[0] = secure_value;
	aes_ctr_words[1] = generation;
	aes_ctr_words[2] = 0;
	aes_ctr_words[3] = 0;
}


std::string nn::hac::ContentArchiveUtil::getFormatVersionAsString(nn::hac::nca::HeaderFormatVersion val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nca::FORMAT_NCA2):
		ss << "NCA2";
		break;
	case (nn::hac::nca::FORMAT_NCA3):
		ss << "NCA3";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ContentArchiveUtil::getProgramContentParititionIndexAsString(nn::hac::nca::ProgramContentPartitionIndex val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nca::PARTITION_CODE):
		ss << "code";
		break;
	case (nn::hac::nca::PARTITION_DATA):
		ss << "data";
		break;
	case (nn::hac::nca::PARTITION_LOGO):
		ss << "logo";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ContentArchiveUtil::getDistributionTypeAsString(nn::hac::nca::DistributionType val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nca::DistributionType::Download):
		ss << "Download";
		break;
	case (nn::hac::nca::DistributionType::GameCard):
		ss << "Game Card";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ContentArchiveUtil::getContentTypeAsString(nn::hac::nca::ContentType val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nca::ContentType::Program):
		ss << "Program";
		break;
	case (nn::hac::nca::ContentType::Meta):
		ss << "Meta";
		break;
	case (nn::hac::nca::ContentType::Control):
		ss << "Control";
		break;
	case (nn::hac::nca::ContentType::Manual):
		ss << "Manual";
		break;
	case (nn::hac::nca::ContentType::Data):
		ss << "Data";
		break;
	case (nn::hac::nca::ContentType::PublicData):
		ss << "PublicData";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ContentArchiveUtil::getFormatTypeAsString(nn::hac::nca::FormatType val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nca::FormatType::RomFs):
		ss << "RomFs";
		break;
	case (nn::hac::nca::FormatType::PartitionFs):
		ss << "PartitionFs";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ContentArchiveUtil::getHashTypeAsString(nn::hac::nca::HashType val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nca::HashType::Auto):
		ss << "Auto";
		break;
	case (nn::hac::nca::HashType::None):
		ss << "None";
		break;
	case (nn::hac::nca::HashType::HierarchicalSha256):
		ss << "HierarchicalSha256";
		break;
	case (nn::hac::nca::HashType::HierarchicalIntegrity):
		ss << "HierarchicalIntegrity";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ContentArchiveUtil::getEncryptionTypeAsString(nn::hac::nca::EncryptionType val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nca::EncryptionType::Auto):
		ss << "Auto";
		break;
	case (nn::hac::nca::EncryptionType::None):
		ss << "None";
		break;
	case (nn::hac::nca::EncryptionType::AesXts):
		ss << "AesXts";
		break;
	case (nn::hac::nca::EncryptionType::AesCtr):
		ss << "AesCtr";
		break;
	case (nn::hac::nca::EncryptionType::AesCtrEx):
		ss << "AesCtrEx";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ContentArchiveUtil::getKeyAreaEncryptionKeyIndexAsString(nn::hac::nca::KeyAreaEncryptionKeyIndex val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nca::KAEK_IDX_APPLICATION):
		ss << "Application";
		break;
	case (nn::hac::nca::KAEK_IDX_OCEAN):
		ss << "Ocean";
		break;
	case (nn::hac::nca::KAEK_IDX_SYSTEM):
		ss << "System";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}