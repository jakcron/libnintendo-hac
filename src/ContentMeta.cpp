#include <nn/hac/ContentMeta.h>

nn::hac::ContentMeta::ContentMeta()
{
	clear();
}

nn::hac::ContentMeta::ContentMeta(const ContentMeta & other)
{
	*this = other;
}

void nn::hac::ContentMeta::operator=(const ContentMeta& other)
{
	if (other.getBytes().size() > 0)
	{
		fromBytes(other.getBytes().data(), other.getBytes().size());
	}
	else
	{
		clear();
		mTitleId = other.mTitleId;
		mTitleVersion = other.mTitleVersion;
		mType = other.mType;
		mAttribute = other.mAttribute;
		mStorageId = other.mStorageId;
		mContentInstallType = other.mContentInstallType;
		mInstallState = other.mInstallState;
		mRequiredDownloadSystemVersion = other.mRequiredDownloadSystemVersion;
		mApplicationMetaExtendedHeader = other.mApplicationMetaExtendedHeader;
		mPatchMetaExtendedHeader = other.mPatchMetaExtendedHeader;
		mAddOnContentMetaExtendedHeader = other.mAddOnContentMetaExtendedHeader;
		mDeltaMetaExtendedHeader = other.mDeltaMetaExtendedHeader;
		mContentInfo = other.mContentInfo;
		mContentMetaInfo = other.mContentMetaInfo;
		mPatchMetaExtendedData = other.mPatchMetaExtendedData;
		mDeltaMetaExtendedData = other.mDeltaMetaExtendedData;
		mSystemUpdateMetaExtendedData = other.mSystemUpdateMetaExtendedData;
		memcpy(mDigest.data(), other.mDigest.data(), mDigest.size());
	}
}

bool nn::hac::ContentMeta::operator==(const ContentMeta& other) const
{
	return (mTitleId == other.mTitleId) \
		&& (mTitleVersion == other.mTitleVersion) \
		&& (mType == other.mType) \
		&& (mAttribute == other.mAttribute) \
		&& (mStorageId == other.mStorageId) \
		&& (mContentInstallType == other.mContentInstallType) \
		&& (mInstallState == other.mInstallState) \
		&& (mRequiredDownloadSystemVersion == other.mRequiredDownloadSystemVersion) \
		&& (mApplicationMetaExtendedHeader == other.mApplicationMetaExtendedHeader) \
		&& (mPatchMetaExtendedHeader == other.mPatchMetaExtendedHeader) \
		&& (mAddOnContentMetaExtendedHeader == other.mAddOnContentMetaExtendedHeader) \
		&& (mDeltaMetaExtendedHeader == other.mDeltaMetaExtendedHeader) \
		&& (mContentInfo == other.mContentInfo) \
		&& (mContentMetaInfo == other.mContentMetaInfo) \
		&& (mPatchMetaExtendedData == other.mPatchMetaExtendedData) \
		&& (mDeltaMetaExtendedData == other.mDeltaMetaExtendedData) \
		&& (mSystemUpdateMetaExtendedData == other.mSystemUpdateMetaExtendedData) \
		&& (memcmp(mDigest.data(), other.mDigest.data(), mDigest.size()) == 0);
}

bool nn::hac::ContentMeta::operator!=(const ContentMeta& other) const
{
	return !(*this == other);
}

void nn::hac::ContentMeta::toBytes()
{
	throw tc::NotImplementedException(kModuleName, "toBytes() not implemented");
}

void nn::hac::ContentMeta::fromBytes(const byte_t* data, size_t len)
{
	// clear member variables
	clear();

	// validate layout
	validateBinary(data, len);

	// get pointer to header structure
	const sContentMetaHeader* hdr = (const sContentMetaHeader*)data;

	mTitleId = hdr->id.unwrap();
	mTitleVersion = hdr->version.unwrap();
	mType = (cnmt::ContentMetaType)hdr->type;
	for (size_t i = 0; i < hdr->attributes.bit_size(); i++)
	{
		if (hdr->attributes.test(i))
		{
			mAttribute.push_back((cnmt::ContentMetaAttributeFlag)i);
		}
	}
	mStorageId = cnmt::StorageId(hdr->storage_id);
	mContentInstallType = cnmt::ContentInstallType(hdr->install_type);
	for (size_t i = 0; i < hdr->install_state.bit_size(); i++)
	{
		if (hdr->install_state.test(i))
		{
			mInstallState.push_back((cnmt::InstallStateFlag)i);
		}
	}
	mRequiredDownloadSystemVersion = hdr->required_download_system_version.unwrap();
	size_t exdata_size = 0;

	// save exheader
	if (hdr->exhdr_size.unwrap() > 0)
	{
		switch (mType)
		{
			case (cnmt::ContentMetaType::Application):
				mApplicationMetaExtendedHeader.fromBytes(data + getExtendedHeaderOffset(), hdr->exhdr_size.unwrap());
				exdata_size = 0;
				break;
			case (cnmt::ContentMetaType::Patch):
				mPatchMetaExtendedHeader.fromBytes(data + getExtendedHeaderOffset(), hdr->exhdr_size.unwrap());
				exdata_size = mPatchMetaExtendedHeader.getExtendedDataSize();
				break;
			case (cnmt::ContentMetaType::AddOnContent):
				mAddOnContentMetaExtendedHeader.fromBytes(data + getExtendedHeaderOffset(), hdr->exhdr_size.unwrap());
				exdata_size = 0;
				break;
			case (cnmt::ContentMetaType::Delta):
				mDeltaMetaExtendedHeader.fromBytes(data + getExtendedHeaderOffset(), hdr->exhdr_size.unwrap());
				exdata_size = mDeltaMetaExtendedHeader.getExtendedDataSize();
				break;
			case (cnmt::ContentMetaType::SystemUpdate):
				mSystemUpdateMetaExtendedHeader.fromBytes(data + getExtendedHeaderOffset(), hdr->exhdr_size.unwrap());
				exdata_size = mSystemUpdateMetaExtendedHeader.getExtendedDataSize();
				break;
			default:
				throw tc::ArgumentOutOfRangeException(kModuleName, "Unhandled extended header for ContentMeta");
				//exdata_size = 0;
				//break;
		}
	}

	// save content info
	if (hdr->content_count.unwrap() > 0)
	{
		const sContentInfo* info = (const sContentInfo*)(data + getContentInfoOffset(hdr->exhdr_size.unwrap()));
		ContentInfo cinfo;
		for (size_t i = 0; i < hdr->content_count.unwrap(); i++)
		{
			cinfo.fromBytes((const byte_t*)&info[i], sizeof(sContentInfo));
			mContentInfo.push_back(cinfo);
		}
	}

	// save content meta info
	if (hdr->content_meta_count.unwrap() > 0)
	{
		const sContentMetaInfo* info = (const sContentMetaInfo*)(data + getContentMetaInfoOffset(hdr->exhdr_size.unwrap(), hdr->content_count.unwrap()));
		ContentMetaInfo cmeta;
		for (size_t i = 0; i < hdr->content_meta_count.unwrap(); i++)
		{	
			cmeta.fromBytes((const byte_t*)&info[i], sizeof(sContentMetaInfo));
			mContentMetaInfo.push_back(cmeta);
		}
	}

	// save exdata
	if (exdata_size > 0)
	{
		switch (mType)
		{
			case (cnmt::ContentMetaType::Patch):
				mPatchMetaExtendedData = tc::ByteData(exdata_size);
				memcpy(mPatchMetaExtendedData.data(), data + getExtendedDataOffset(hdr->exhdr_size.unwrap(), hdr->content_count.unwrap(), hdr->content_meta_count.unwrap()), exdata_size);
				break;
			case (cnmt::ContentMetaType::Delta):
				mDeltaMetaExtendedData = tc::ByteData(exdata_size);
				memcpy(mDeltaMetaExtendedData.data(), data + getExtendedDataOffset(hdr->exhdr_size.unwrap(), hdr->content_count.unwrap(), hdr->content_meta_count.unwrap()), exdata_size);
				break;
			case (cnmt::ContentMetaType::SystemUpdate):
				mSystemUpdateMetaExtendedData.fromBytes(data + getExtendedDataOffset(hdr->exhdr_size.unwrap(), hdr->content_count.unwrap(), hdr->content_meta_count.unwrap()), exdata_size);
				break;
			default:
				throw tc::ArgumentOutOfRangeException(kModuleName, "Unhandled extended data for ContentMeta");
				//exdata_size = 0;
				//break;
		}
	}

	// save digest
	memcpy(mDigest.data(), data + getDigestOffset(hdr->exhdr_size.unwrap(), hdr->content_count.unwrap(), hdr->content_meta_count.unwrap(), exdata_size), mDigest.size());

	// save raw binary
	mRawBinary = tc::ByteData(getDigestOffset(hdr->exhdr_size.unwrap(), hdr->content_count.unwrap(), hdr->content_meta_count.unwrap(), exdata_size) + mDigest.size());

	memcpy(mRawBinary.data(), data, mRawBinary.size());
}

const tc::ByteData& nn::hac::ContentMeta::getBytes() const
{
	return mRawBinary;
}

void nn::hac::ContentMeta::clear()
{
	mRawBinary = tc::ByteData();
	mTitleId = 0;
	mTitleVersion = 0;
	mType = cnmt::ContentMetaType::SystemProgram;
	mAttribute.clear();
	mStorageId = cnmt::StorageId::None;
	mContentInstallType = cnmt::ContentInstallType::Full;
	mInstallState.clear();
	mRequiredDownloadSystemVersion = 0;
	mApplicationMetaExtendedHeader.clear();
	mPatchMetaExtendedHeader.clear();
	mAddOnContentMetaExtendedHeader.clear();
	mDeltaMetaExtendedHeader.clear();
	mSystemUpdateMetaExtendedHeader.clear();
	mContentInfo.clear();
	mContentMetaInfo.clear();
	mPatchMetaExtendedData = tc::ByteData();
	mDeltaMetaExtendedData = tc::ByteData();
	mSystemUpdateMetaExtendedData.clear();
	memset(mDigest.data(), 0, mDigest.size());
}

uint64_t nn::hac::ContentMeta::getTitleId() const
{
	return mTitleId;
}

void nn::hac::ContentMeta::setTitleId(uint64_t title_id)
{
	mTitleId = title_id;
}

uint32_t nn::hac::ContentMeta::getTitleVersion() const
{
	return mTitleVersion;
}

void nn::hac::ContentMeta::setTitleVersion(uint32_t version)
{
	mTitleVersion = version;
}

nn::hac::cnmt::ContentMetaType nn::hac::ContentMeta::getContentMetaType() const
{
	return mType;
}

void nn::hac::ContentMeta::setContentMetaType(nn::hac::cnmt::ContentMetaType type)
{
	mType = type;
}

const std::vector<nn::hac::cnmt::ContentMetaAttributeFlag>& nn::hac::ContentMeta::getAttribute() const
{
	return mAttribute;
}

void nn::hac::ContentMeta::setAttribute(const std::vector<nn::hac::cnmt::ContentMetaAttributeFlag>& attr)
{
	mAttribute = attr;
}

nn::hac::cnmt::StorageId nn::hac::ContentMeta::getStorageId() const
{
	return mStorageId;
}

void nn::hac::ContentMeta::setStorageId(nn::hac::cnmt::StorageId storage_id)
{
	mStorageId = storage_id;
}

nn::hac::cnmt::ContentInstallType nn::hac::ContentMeta::getContentInstallType() const
{
	return mContentInstallType;
}

void nn::hac::ContentMeta::setContentInstallType(nn::hac::cnmt::ContentInstallType install_type)
{
	mContentInstallType = install_type;
}

const std::vector<nn::hac::cnmt::InstallStateFlag>& nn::hac::ContentMeta::getInstallState() const
{
	return mInstallState;
}

void nn::hac::ContentMeta::setInstallState(const std::vector<nn::hac::cnmt::InstallStateFlag>& install_state)
{
	mInstallState = install_state;
}

uint32_t nn::hac::ContentMeta::getRequiredDownloadSystemVersion() const
{
	return mRequiredDownloadSystemVersion;
}

void nn::hac::ContentMeta::setRequiredDownloadSystemVersion(uint32_t version)
{
	mRequiredDownloadSystemVersion = version;
}

const nn::hac::ApplicationMetaExtendedHeader& nn::hac::ContentMeta::getApplicationMetaExtendedHeader() const
{
	return mApplicationMetaExtendedHeader;
}

void nn::hac::ContentMeta::setApplicationMetaExtendedHeader(const nn::hac::ApplicationMetaExtendedHeader& exhdr)
{
	mApplicationMetaExtendedHeader = exhdr;
}

const nn::hac::PatchMetaExtendedHeader& nn::hac::ContentMeta::getPatchMetaExtendedHeader() const
{
	return mPatchMetaExtendedHeader;
}

void nn::hac::ContentMeta::setPatchMetaExtendedHeader(const nn::hac::PatchMetaExtendedHeader& exhdr)
{
	mPatchMetaExtendedHeader = exhdr;
}

const nn::hac::AddOnContentMetaExtendedHeader& nn::hac::ContentMeta::getAddOnContentMetaExtendedHeader() const
{
	return mAddOnContentMetaExtendedHeader;
}

void nn::hac::ContentMeta::setAddOnContentMetaExtendedHeader(const nn::hac::AddOnContentMetaExtendedHeader& exhdr)
{
	mAddOnContentMetaExtendedHeader = exhdr;
}

const nn::hac::DeltaMetaExtendedHeader& nn::hac::ContentMeta::getDeltaMetaExtendedHeader() const
{
	return mDeltaMetaExtendedHeader;
}

void nn::hac::ContentMeta::setDeltaMetaExtendedHeader(const nn::hac::DeltaMetaExtendedHeader& exhdr)
{
	mDeltaMetaExtendedHeader = exhdr;
}

const nn::hac::SystemUpdateMetaExtendedHeader& nn::hac::ContentMeta::getSystemUpdateMetaExtendedHeader() const
{
	return mSystemUpdateMetaExtendedHeader;
}

void nn::hac::ContentMeta::setSystemUpdateMetaExtendedHeader(const nn::hac::SystemUpdateMetaExtendedHeader& exhdr)
{
	mSystemUpdateMetaExtendedHeader = exhdr;
}

const std::vector<nn::hac::ContentInfo>& nn::hac::ContentMeta::getContentInfo() const
{
	return mContentInfo;
}

void nn::hac::ContentMeta::setContentInfo(const std::vector<nn::hac::ContentInfo>& info)
{
	mContentInfo = info;
}

const std::vector<nn::hac::ContentMetaInfo>& nn::hac::ContentMeta::getContentMetaInfo() const
{
	return mContentMetaInfo;
}

void nn::hac::ContentMeta::setContentMetaInfo(const std::vector<nn::hac::ContentMetaInfo>& info)
{
	mContentMetaInfo = info;
}

const tc::ByteData & nn::hac::ContentMeta::getPatchMetaExtendedData() const
{
	return mPatchMetaExtendedData;
}

void nn::hac::ContentMeta::setPatchMetaExtendedData(const tc::ByteData& exdata)
{
	mPatchMetaExtendedData = exdata;
}

const tc::ByteData & nn::hac::ContentMeta::getDeltaMetaExtendedData() const
{
	return mDeltaMetaExtendedData;
}

void nn::hac::ContentMeta::setDeltaMetaExtendedData(const tc::ByteData& exdata)
{
	mDeltaMetaExtendedData = exdata;
}

const nn::hac::SystemUpdateMetaExtendedData& nn::hac::ContentMeta::getSystemUpdateMetaExtendedData() const
{
	return mSystemUpdateMetaExtendedData;
}

void nn::hac::ContentMeta::setSystemUpdateMetaExtendedData(const nn::hac::SystemUpdateMetaExtendedData& exdata)
{
	mSystemUpdateMetaExtendedData = exdata;
}

const nn::hac::cnmt::digest_t & nn::hac::ContentMeta::getDigest() const
{
	return mDigest;
}

void nn::hac::ContentMeta::setDigest(const nn::hac::cnmt::digest_t& digest)
{
	mDigest = digest;
}

bool nn::hac::ContentMeta::validateExtendedHeaderSize(cnmt::ContentMetaType type, size_t exhdrSize) const
{
	bool validSize = false;

	switch (type)
	{
		case (cnmt::ContentMetaType::Application):
			validSize = (exhdrSize == sizeof(sApplicationMetaExtendedHeader));
			break;
		case (cnmt::ContentMetaType::Patch):
			validSize = (exhdrSize == sizeof(sPatchMetaExtendedHeader));
			break;
		case (cnmt::ContentMetaType::AddOnContent):
			validSize = (exhdrSize == sizeof(sAddOnContentMetaExtendedHeader));
			break;
		case (cnmt::ContentMetaType::Delta):
			validSize = (exhdrSize == sizeof(sDeltaMetaExtendedHeader));
			break;
		case (cnmt::ContentMetaType::SystemUpdate):
			validSize = (exhdrSize == sizeof(sSystemUpdateMetaExtendedHeader));
			break;
		default:
			validSize = (exhdrSize == 0);
	}

	return validSize;
}

size_t nn::hac::ContentMeta::getExtendedDataSize(cnmt::ContentMetaType type, const byte_t * data) const
{
	size_t exdata_len = 0;
	if (type == cnmt::ContentMetaType::Patch)
	{
		const sPatchMetaExtendedHeader* exhdr = (const sPatchMetaExtendedHeader*)(data);
		exdata_len = exhdr->extended_data_size.unwrap();
	}
	else if (type == cnmt::ContentMetaType::Delta)
	{
		const sDeltaMetaExtendedHeader* exhdr = (const sDeltaMetaExtendedHeader*)(data);
		exdata_len = exhdr->extended_data_size.unwrap();
	}
	else if (type == cnmt::ContentMetaType::SystemUpdate)
	{
		const sSystemUpdateMetaExtendedHeader* exhdr = (const sSystemUpdateMetaExtendedHeader*)(data);
		exdata_len = exhdr->extended_data_size.unwrap();
	}
	return exdata_len;
}

void nn::hac::ContentMeta::validateBinary(const byte_t * data, size_t len) const
{
	// check if it is large enough to read the header
	if (len < sizeof(sContentMetaHeader))
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Binary too small");
	}

	// get pointer to header structure
	const sContentMetaHeader* hdr = (const sContentMetaHeader*)data;

	// validate extended header size
	if (validateExtendedHeaderSize((cnmt::ContentMetaType)hdr->type, hdr->exhdr_size.unwrap()) == false)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Invalid extended header size");
	}

	// check binary size again for new minimum size
	if (len < getTotalSize(hdr->exhdr_size.unwrap(), hdr->content_count.unwrap(), hdr->content_meta_count.unwrap(), 0))
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Binary too small");
	}

	// check binary size again with extended data size
	if (len < getTotalSize(hdr->exhdr_size.unwrap(), hdr->content_count.unwrap(), hdr->content_meta_count.unwrap(), getExtendedDataSize((cnmt::ContentMetaType)hdr->type, data + getExtendedHeaderOffset())))
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Binary too small");
	}
}