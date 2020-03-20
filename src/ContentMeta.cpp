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
		mExtendedData = other.mExtendedData;
		memcpy(mDigest.data, other.mDigest.data, cnmt::kDigestLen);
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
		&& (mExtendedData == other.mExtendedData) \
		&& (memcmp(mDigest.data, other.mDigest.data, cnmt::kDigestLen) == 0);
}

bool nn::hac::ContentMeta::operator!=(const ContentMeta& other) const
{
	return !(*this == other);
}

void nn::hac::ContentMeta::toBytes()
{
	throw fnd::Exception(kModuleName, "toBytes() not implemented");
}

void nn::hac::ContentMeta::fromBytes(const byte_t* data, size_t len)
{
	// clear member variables
	clear();

	// validate layout
	validateBinary(data, len);

	// get pointer to header structure
	const sContentMetaHeader* hdr = (const sContentMetaHeader*)data;

	mTitleId = hdr->id.get();
	mTitleVersion = hdr->version.get();
	mType = (cnmt::ContentMetaType)hdr->type;
	mAttribute = hdr->attributes;
	mStorageId = cnmt::StorageId(hdr->storage_id);
	mContentInstallType = cnmt::ContentInstallType(hdr->install_type);
	mInstallState = hdr->install_state;
	mRequiredDownloadSystemVersion = hdr->required_download_system_version.get();
	size_t exdata_size = 0;

	// save exheader
	if (hdr->exhdr_size.get() > 0)
	{
		switch (mType)
		{
			case (cnmt::ContentMetaType::Application):
				mApplicationMetaExtendedHeader.fromBytes(data + getExtendedHeaderOffset(), hdr->exhdr_size.get());
				exdata_size = 0;
				break;
			case (cnmt::ContentMetaType::Patch):
				mPatchMetaExtendedHeader.fromBytes(data + getExtendedHeaderOffset(), hdr->exhdr_size.get());
				exdata_size = mPatchMetaExtendedHeader.getExtendedDataSize();
				break;
			case (cnmt::ContentMetaType::AddOnContent):
				mAddOnContentMetaExtendedHeader.fromBytes(data + getExtendedHeaderOffset(), hdr->exhdr_size.get());
				exdata_size = 0;
				break;
			case (cnmt::ContentMetaType::Delta):
				mDeltaMetaExtendedHeader.fromBytes(data + getExtendedHeaderOffset(), hdr->exhdr_size.get());
				exdata_size = mDeltaMetaExtendedHeader.getExtendedDataSize();
				break;
			default:
				throw fnd::Exception(kModuleName, "Unhandled extended header for ContentMeta");
				//exdata_size = 0;
				//break;
		}
	}

	// save content info
	if (hdr->content_count.get() > 0)
	{
		const sContentInfo* info = (const sContentInfo*)(data + getContentInfoOffset(hdr->exhdr_size.get()));
		ContentInfo cinfo;
		for (size_t i = 0; i < hdr->content_count.get(); i++)
		{
			cinfo.fromBytes((const byte_t*)&info[i], sizeof(sContentInfo));
			mContentInfo.addElement(cinfo);
		}
	}

	// save content meta info
	if (hdr->content_meta_count.get() > 0)
	{
		const sContentMetaInfo* info = (const sContentMetaInfo*)(data + getContentMetaInfoOffset(hdr->exhdr_size.get(), hdr->content_count.get()));
		ContentMetaInfo cmeta;
		for (size_t i = 0; i < hdr->content_meta_count.get(); i++)
		{	
			cmeta.fromBytes((const byte_t*)&info[i], sizeof(sContentMetaInfo));
			mContentMetaInfo.addElement(cmeta);
		}
	}

	// save exdata
	if (exdata_size > 0)
	{
		mExtendedData.alloc(exdata_size);
		memcpy(mExtendedData.data(), data + getExtendedDataOffset(hdr->exhdr_size.get(), hdr->content_count.get(), hdr->content_meta_count.get()), exdata_size);
	}

	// save digest
	memcpy(mDigest.data, data + getDigestOffset(hdr->exhdr_size.get(), hdr->content_count.get(), hdr->content_meta_count.get(), exdata_size), cnmt::kDigestLen);
}

const fnd::Vec<byte_t>& nn::hac::ContentMeta::getBytes() const
{
	return mRawBinary;
}

void nn::hac::ContentMeta::clear()
{
	mRawBinary.clear();
	mTitleId = 0;
	mTitleVersion = 0;
	mType = cnmt::ContentMetaType::SystemProgram;
	mAttribute = 0;
	mStorageId = cnmt::StorageId::None;
	mContentInstallType = cnmt::ContentInstallType::Full;
	mInstallState = 0;
	mRequiredDownloadSystemVersion = 0;
	mApplicationMetaExtendedHeader.clear();
	mPatchMetaExtendedHeader.clear();
	mAddOnContentMetaExtendedHeader.clear();
	mDeltaMetaExtendedHeader.clear();
	mContentInfo.clear();
	mContentMetaInfo.clear();
	mExtendedData.clear();
	memset(mDigest.data, 0, cnmt::kDigestLen);
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

void nn::hac::ContentMeta::setContentMetaType(cnmt::ContentMetaType type)
{
	mType = type;
}

const nn::hac::cnmt::ContentMetaAttribute& nn::hac::ContentMeta::getAttribute() const
{
	return mAttribute;
}

void nn::hac::ContentMeta::setAttribute(const nn::hac::cnmt::ContentMetaAttribute& attr)
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

nn::hac::cnmt::InstallState nn::hac::ContentMeta::getInstallState() const
{
	return mInstallState;
}

void nn::hac::ContentMeta::setInstallState(nn::hac::cnmt::InstallState install_state)
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

void nn::hac::ContentMeta::setApplicationMetaExtendedHeader(const ApplicationMetaExtendedHeader& exhdr)
{
	mApplicationMetaExtendedHeader = exhdr;
}

const nn::hac::PatchMetaExtendedHeader& nn::hac::ContentMeta::getPatchMetaExtendedHeader() const
{
	return mPatchMetaExtendedHeader;
}

void nn::hac::ContentMeta::setPatchMetaExtendedHeader(const PatchMetaExtendedHeader& exhdr)
{
	mPatchMetaExtendedHeader = exhdr;
}

const nn::hac::AddOnContentMetaExtendedHeader& nn::hac::ContentMeta::getAddOnContentMetaExtendedHeader() const
{
	return mAddOnContentMetaExtendedHeader;
}

void nn::hac::ContentMeta::setAddOnContentMetaExtendedHeader(const AddOnContentMetaExtendedHeader& exhdr)
{
	mAddOnContentMetaExtendedHeader = exhdr;
}

const nn::hac::DeltaMetaExtendedHeader& nn::hac::ContentMeta::getDeltaMetaExtendedHeader() const
{
	return mDeltaMetaExtendedHeader;
}

void nn::hac::ContentMeta::setDeltaMetaExtendedHeader(const DeltaMetaExtendedHeader& exhdr)
{
	mDeltaMetaExtendedHeader = exhdr;
}

const fnd::List<nn::hac::ContentInfo>& nn::hac::ContentMeta::getContentInfo() const
{
	return mContentInfo;
}

void nn::hac::ContentMeta::setContentInfo(const fnd::List<nn::hac::ContentInfo>& info)
{
	mContentInfo = info;
}

const fnd::List<nn::hac::ContentMetaInfo>& nn::hac::ContentMeta::getContentMetaInfo() const
{
	return mContentMetaInfo;
}

void nn::hac::ContentMeta::setContentMetaInfo(const fnd::List<nn::hac::ContentMetaInfo>& info)
{
	mContentMetaInfo = info;
}

const fnd::Vec<byte_t> & nn::hac::ContentMeta::getExtendedData() const
{
	return mExtendedData;
}

void nn::hac::ContentMeta::setExtendedData(const fnd::Vec<byte_t>& data)
{
	mExtendedData = data;
}

const nn::hac::cnmt::sDigest & nn::hac::ContentMeta::getDigest() const
{
	return mDigest;
}

void nn::hac::ContentMeta::setDigest(const nn::hac::cnmt::sDigest& digest)
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
		exdata_len = exhdr->extended_data_size.get();
	}
	else if (type == cnmt::ContentMetaType::Delta)
	{
		const sDeltaMetaExtendedHeader* exhdr = (const sDeltaMetaExtendedHeader*)(data);
		exdata_len = exhdr->extended_data_size.get();
	}
	return exdata_len;
}

void nn::hac::ContentMeta::validateBinary(const byte_t * data, size_t len) const
{
	// check if it is large enough to read the header
	if (len < sizeof(sContentMetaHeader))
	{
		throw fnd::Exception(kModuleName, "Binary too small");
	}

	// get pointer to header structure
	const sContentMetaHeader* hdr = (const sContentMetaHeader*)data;

	// validate extended header size
	if (validateExtendedHeaderSize((cnmt::ContentMetaType)hdr->type, hdr->exhdr_size.get()) == false)
	{
		throw fnd::Exception(kModuleName, "Invalid extended header size");
	}

	// check binary size again for new minimum size
	if (len < getTotalSize(hdr->exhdr_size.get(), hdr->content_count.get(), hdr->content_meta_count.get(), 0))
	{
		throw fnd::Exception(kModuleName, "Binary too small");
	}

	// check binary size again with extended data size
	if (len < getTotalSize(hdr->exhdr_size.get(), hdr->content_count.get(), hdr->content_meta_count.get(), getExtendedDataSize((cnmt::ContentMetaType)hdr->type, data + getExtendedHeaderOffset())))
	{
		throw fnd::Exception(kModuleName, "Binary too small");
	}
}