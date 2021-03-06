#include <cstring>
#include <nn/hac/FileSystemAccessControl.h>

nn::hac::FileSystemAccessControl::FileSystemAccessControl()
{
	clear();
}

nn::hac::FileSystemAccessControl::FileSystemAccessControl(const FileSystemAccessControl & other)
{
	*this = other;
}

void nn::hac::FileSystemAccessControl::operator=(const FileSystemAccessControl & other)
{
	mRawBinary = other.mRawBinary;
	mVersion = other.mVersion;
	mFsAccess = other.mFsAccess;
	mContentOwnerIdList = other.mContentOwnerIdList;
	mSaveDataOwnerIdList = other.mSaveDataOwnerIdList;
}

bool nn::hac::FileSystemAccessControl::operator==(const FileSystemAccessControl & other) const
{
	return (mVersion == other.mVersion) \
		&& (mFsAccess == other.mFsAccess) \
		&& (mContentOwnerIdList == other.mContentOwnerIdList) \
		&& (mSaveDataOwnerIdList == other.mSaveDataOwnerIdList);
}

bool nn::hac::FileSystemAccessControl::operator!=(const FileSystemAccessControl & other) const
{
	return !(*this == other);
}

void nn::hac::FileSystemAccessControl::toBytes()
{
	// determine section layout
	struct sLayout {
		uint32_t offset, size;
	} content, savedata;

	content.offset = (uint32_t)align(sizeof(sFacHeader), fac::kSectionAlignSize);
	if (mContentOwnerIdList.size() > 0)
		content.size = (uint32_t)(sizeof(uint32_t) + mContentOwnerIdList.size() * sizeof(uint64_t));
	else
		content.size = 0;

	savedata.offset = (uint32_t)(content.offset + (content.size > 0 ? align(content.size, fac::kSectionAlignSize) : 0));
	if (mSaveDataOwnerIdList.size() > 0)
		savedata.size = (uint32_t)(sizeof(uint32_t) + align(mSaveDataOwnerIdList.size(), fac::kSectionAlignSize) + mSaveDataOwnerIdList.size() * sizeof(uint64_t));
	else
		savedata.size = 0;
	

	// get total size
	size_t total_size = _MAX(_MAX(content.offset + content.size, savedata.offset + savedata.size), align(sizeof(sFacHeader), fac::kSectionAlignSize)); 

	mRawBinary.alloc(total_size);
	sFacHeader* hdr = (sFacHeader*)mRawBinary.data();

	// set type
	hdr->version = mVersion;

	// flags
	hdr->fac_flags = mFsAccess.to_ullong();

	// set offset/size
	hdr->content_owner_ids.offset = content.offset;
	if (content.size > 0)
		hdr->content_owner_ids.size = content.size;
	hdr->save_data_owner_ids.offset = savedata.offset;
	if (savedata.size > 0)
		hdr->save_data_owner_ids.size = savedata.size;

	// set ids
	le_uint32_t* content_owner_id_num = (le_uint32_t*)(mRawBinary.data() + content.offset);
	le_uint64_t* content_owner_ids = (le_uint64_t*)(mRawBinary.data() + content.offset + sizeof(uint32_t));
	content_owner_id_num->set((uint32_t)mContentOwnerIdList.size());
	for (size_t i = 0; i < mContentOwnerIdList.size(); i++)
	{
		content_owner_ids[i] = mContentOwnerIdList[i];
	}

	le_uint32_t* save_data_owner_id_num = (le_uint32_t*)(mRawBinary.data() + savedata.offset);
	byte_t* save_data_owner_id_accessibility_array = (mRawBinary.data() + savedata.offset + sizeof(uint32_t));
	le_uint64_t* save_data_owner_ids = (le_uint64_t*)(mRawBinary.data() + savedata.offset + sizeof(uint32_t) + align(mSaveDataOwnerIdList.size(), sizeof(uint32_t)));
	save_data_owner_id_num->set((uint32_t)mSaveDataOwnerIdList.size());
	for (size_t i = 0; i < mSaveDataOwnerIdList.size(); i++)
	{
		save_data_owner_id_accessibility_array[i] = (byte_t)mSaveDataOwnerIdList[i].access_type;
		save_data_owner_ids[i] = mSaveDataOwnerIdList[i].id;
	}
}

void nn::hac::FileSystemAccessControl::fromBytes(const byte_t* data, size_t len)
{
	// check size
	if (len < sizeof(sFacHeader))
	{
		throw fnd::Exception(kModuleName, "FileSystemAccessControlInfo binary is too small");
	}
	
	// clear variables
	clear();

	// save a copy of the header
	sFacHeader hdr;
	memcpy((void*)&hdr, data, sizeof(sFacHeader));

	// check format version
	if (hdr.version.get() != fac::kFacFormatVersion)
	{
		throw fnd::Exception(kModuleName, "FileSystemAccessControlInfo format version unsupported");
	}
	
	// get total size
	size_t total_size = _MAX(_MAX(hdr.content_owner_ids.offset.get() + hdr.content_owner_ids.size.get(), hdr.save_data_owner_ids.offset.get() + hdr.save_data_owner_ids.size.get()), align(sizeof(sFacHeader), fac::kSectionAlignSize));

	// validate binary size
	if (len < total_size)
	{
		throw fnd::Exception(kModuleName, "FileSystemAccessControlInfo binary is too small");
	}

	// allocate memory
	mRawBinary.alloc(total_size);
	memcpy(mRawBinary.data(), data, mRawBinary.size());

	// save variables
	mVersion = hdr.version.get();
	mFsAccess = hdr.fac_flags.get();

	// save ids
	if (hdr.content_owner_ids.size.get() > 0)
	{
		size_t content_owner_id_num = ((le_uint32_t*)(mRawBinary.data() + hdr.content_owner_ids.offset.get()))->get();
		le_uint64_t* content_owner_ids = (le_uint64_t*)(mRawBinary.data() + hdr.content_owner_ids.offset.get() + sizeof(uint32_t));
		for (size_t i = 0; i < content_owner_id_num; i++)
		{
			mContentOwnerIdList.addElement(content_owner_ids[i].get());
		}
	}
	if (hdr.save_data_owner_ids.size.get() > 0)
	{
		size_t save_data_owner_id_num = ((le_uint32_t*)(mRawBinary.data() + hdr.save_data_owner_ids.offset.get()))->get();
		byte_t* save_data_owner_id_accessibility_array = (mRawBinary.data() + hdr.save_data_owner_ids.offset.get() + sizeof(uint32_t));
		le_uint64_t* save_data_owner_ids = (le_uint64_t*)(mRawBinary.data() + hdr.save_data_owner_ids.offset.get() + sizeof(uint32_t) + align(save_data_owner_id_num, fac::kSectionAlignSize));
		for (size_t i = 0; i < save_data_owner_id_num; i++)
		{
			mSaveDataOwnerIdList.addElement({ (fac::SaveDataOwnerIdAccessType)save_data_owner_id_accessibility_array[i], save_data_owner_ids[i].get() });
		}
	}
}

const fnd::Vec<byte_t>& nn::hac::FileSystemAccessControl::getBytes() const
{
	return mRawBinary;
}

void nn::hac::FileSystemAccessControl::clear()
{
	mRawBinary.clear();
	mVersion = 0;
	mFsAccess.reset();
	mContentOwnerIdList.clear();
	mSaveDataOwnerIdList.clear();
}

uint32_t nn::hac::FileSystemAccessControl::getFormatVersion() const
{
	return mVersion;
}

void nn::hac::FileSystemAccessControl::setFormatVersion(uint32_t format_version)
{
	mVersion = format_version;
}

const nn::hac::fac::FsAccess& nn::hac::FileSystemAccessControl::getFsAccess() const
{
	return mFsAccess;
}

void nn::hac::FileSystemAccessControl::setFsAccess(const nn::hac::fac::FsAccess& access)
{
	mFsAccess = access;
}

const fnd::List<uint64_t>& nn::hac::FileSystemAccessControl::getContentOwnerIdList() const
{
	return mContentOwnerIdList;
}

void nn::hac::FileSystemAccessControl::setContentOwnerIdList(const fnd::List<uint64_t>& list)
{
	mContentOwnerIdList = list;
}

const fnd::List<nn::hac::FileSystemAccessControl::sSaveDataOwnerId>& nn::hac::FileSystemAccessControl::getSaveDataOwnerIdList() const
{
	return mSaveDataOwnerIdList;
}

void nn::hac::FileSystemAccessControl::setSaveDataOwnerIdList(const fnd::List<sSaveDataOwnerId>& list)
{
	mSaveDataOwnerIdList = list;
}