#include <nn/hac/KernelInitialProcessHeader.h>

nn::hac::KernelInitialProcessHeader::KernelInitialProcessHeader()
{
	clear();
}

nn::hac::KernelInitialProcessHeader::KernelInitialProcessHeader(const KernelInitialProcessHeader& other)
{
	*this = other;
}

void nn::hac::KernelInitialProcessHeader::operator=(const KernelInitialProcessHeader& other)
{
	clear();
	this->mName = other.mName;
	this->mTitleId = other.mTitleId;
	this->mVersion = other.mVersion;
	this->mIs64BitInstructionFlag = other.mIs64BitInstructionFlag;
	this->mIs64BitAddressSpaceFlag = other.mIs64BitAddressSpaceFlag;
	this->mUseSecureMemoryFlag = other.mUseSecureMemoryFlag;
	this->mMainThreadPriority = other.mMainThreadPriority;
	this->mMainThreadCpuId = other.mMainThreadCpuId;
	this->mMainThreadStackSize = other.mMainThreadStackSize;
	this->mTextInfo = other.mTextInfo;
	this->mRoInfo = other.mRoInfo;
	this->mDataInfo = other.mDataInfo;
	this->mBssSize = other.mBssSize;
	this->mKernelCapabilities = other.mKernelCapabilities;
}

bool nn::hac::KernelInitialProcessHeader::operator==(const KernelInitialProcessHeader& other) const
{
	return (this->mName == other.mName) \
		&& (this->mTitleId == other.mTitleId) \
		&& (this->mVersion == other.mVersion) \
		&& (this->mIs64BitInstructionFlag == other.mIs64BitInstructionFlag) \
		&& (this->mIs64BitAddressSpaceFlag == other.mIs64BitAddressSpaceFlag) \
		&& (this->mUseSecureMemoryFlag == other.mUseSecureMemoryFlag) \
		&& (this->mMainThreadPriority == other.mMainThreadPriority) \
		&& (this->mMainThreadCpuId == other.mMainThreadCpuId) \
		&& (this->mMainThreadStackSize == other.mMainThreadStackSize) \
		&& (this->mTextInfo == other.mTextInfo) \
		&& (this->mRoInfo == other.mRoInfo) \
		&& (this->mDataInfo == other.mDataInfo) \
		&& (this->mBssSize == other.mBssSize) \
		&& (this->mKernelCapabilities == other.mKernelCapabilities);
}

bool nn::hac::KernelInitialProcessHeader::operator!=(const KernelInitialProcessHeader& other) const
{
	return !(*this == other);
}

void nn::hac::KernelInitialProcessHeader::toBytes()
{
	mRawBinary = tc::ByteData(sizeof(sKipHeader));
	nn::hac::sKipHeader* hdr = (nn::hac::sKipHeader*)mRawBinary.data();

	// set header identifers
	hdr->st_magic.wrap(kip::kKipStructMagic);

	// properties
	hdr->name.encode(mName);
	hdr->title_id.wrap(mTitleId);
	hdr->version.wrap(mVersion);
	hdr->flags.is_64bit_instruction = mIs64BitInstructionFlag;
	hdr->flags.is_64bit_address_space = mIs64BitAddressSpaceFlag;
	hdr->flags.use_secure_memory = mUseSecureMemoryFlag;
	hdr->main_thread_priority = mMainThreadPriority;
	hdr->main_thread_cpu_id = mMainThreadCpuId;
	hdr->main_thread_stack_size.wrap(mMainThreadStackSize);

	// kernel caps
	mKernelCapabilities.toBytes();
	if (mKernelCapabilities.getBytes().size() > hdr->capabilities.size())
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Too many kernel capabilities");
	}
	memcpy(hdr->capabilities.data(), mKernelCapabilities.getBytes().data(), mKernelCapabilities.getBytes().size());
	
	// stub remaining entries
	if (mKernelCapabilities.getBytes().size() < hdr->capabilities.size())
	{
		memset(hdr->capabilities.data() + mKernelCapabilities.getBytes().size(), 0xff, hdr->capabilities.size() - mKernelCapabilities.getBytes().size());
	}	

	// set bss size
	hdr->bss.file_size.wrap(0);
	hdr->bss.memory_offset.wrap(0);
	hdr->bss.memory_size.wrap(mBssSize);

	// set text segment
	hdr->text.memory_offset.wrap(mTextInfo.memory_layout.offset);
	hdr->text.memory_size.wrap(mTextInfo.memory_layout.size);
	hdr->text.file_size.wrap(mTextInfo.file_layout.size);
	hdr->flags.text_compress = mTextInfo.is_compressed;

	// set ro segment
	hdr->ro.memory_offset.wrap(mRoInfo.memory_layout.offset);
	hdr->ro.memory_size.wrap(mRoInfo.memory_layout.size);
	hdr->ro.file_size.wrap(mRoInfo.file_layout.size);
	hdr->flags.ro_compress = mRoInfo.is_compressed;

	// set data segment
	hdr->data.memory_offset.wrap(mDataInfo.memory_layout.offset);
	hdr->data.memory_size.wrap(mDataInfo.memory_layout.size);
	hdr->data.file_size.wrap(mDataInfo.file_layout.size);
	hdr->flags.data_compress = mDataInfo.is_compressed;
}

void nn::hac::KernelInitialProcessHeader::fromBytes(const byte_t* data, size_t len)
{
	// check input data size
	if (len < sizeof(sKipHeader))
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "KIP header size is too small");
	}

	// clear internal members
	clear();

	// allocate internal local binary copy
	mRawBinary = tc::ByteData(sizeof(sKipHeader));
	memcpy(mRawBinary.data(), data, mRawBinary.size());

	// get sKipHeader ptr
	const nn::hac::sKipHeader* hdr = (const nn::hac::sKipHeader*)mRawBinary.data();
	
	// check KIP signature
	if (hdr->st_magic.unwrap() != kip::kKipStructMagic)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "KIP header corrupt (unrecognised header signature)");
	}

	// properties
	mName = hdr->name.decode();
	mTitleId = hdr->title_id.unwrap();
	mVersion = hdr->version.unwrap();
	mIs64BitInstructionFlag = hdr->flags.is_64bit_instruction;
	mIs64BitAddressSpaceFlag = hdr->flags.is_64bit_address_space;
	mUseSecureMemoryFlag = hdr->flags.use_secure_memory;
	mMainThreadPriority = hdr->main_thread_priority;
	mMainThreadCpuId = hdr->main_thread_cpu_id;
	mMainThreadStackSize = hdr->main_thread_stack_size.unwrap();
	mKernelCapabilities.fromBytes(hdr->capabilities.data(), hdr->capabilities.size());

	// code segment info
	mTextInfo.file_layout.offset = sizeof(sKipHeader);
	mTextInfo.file_layout.size = hdr->text.file_size.unwrap();
	mTextInfo.memory_layout.offset = hdr->text.memory_offset.unwrap();
	mTextInfo.memory_layout.size = hdr->text.memory_size.unwrap();
	mTextInfo.is_compressed = hdr->flags.text_compress;

	mRoInfo.file_layout.offset = mTextInfo.file_layout.offset + mTextInfo.file_layout.size;
	mRoInfo.file_layout.size = hdr->ro.file_size.unwrap();
	mRoInfo.memory_layout.offset = hdr->ro.memory_offset.unwrap();
	mRoInfo.memory_layout.size = hdr->ro.memory_size.unwrap();
	mRoInfo.is_compressed = hdr->flags.ro_compress;

	mDataInfo.file_layout.offset = mRoInfo.file_layout.offset + mRoInfo.file_layout.size;
	mDataInfo.file_layout.size = hdr->data.file_size.unwrap();
	mDataInfo.memory_layout.offset = hdr->data.memory_offset.unwrap();
	mDataInfo.memory_layout.size = hdr->data.memory_size.unwrap();
	mDataInfo.is_compressed = hdr->flags.data_compress;

	mBssSize = hdr->bss.memory_size.unwrap();
}

const tc::ByteData& nn::hac::KernelInitialProcessHeader::getBytes() const
{
	return mRawBinary;
}

void nn::hac::KernelInitialProcessHeader::clear()
{
	mRawBinary = tc::ByteData();
	mName.clear();
	mTitleId = 0;
	mVersion = 0;
	mIs64BitInstructionFlag = false;
	mIs64BitAddressSpaceFlag = false;
	mUseSecureMemoryFlag = false;
	mMainThreadPriority = 0;
	mMainThreadCpuId = 0;
	mMainThreadStackSize = 0;
	mTextInfo = sCodeSegment();
	mRoInfo = sCodeSegment();
	mDataInfo = sCodeSegment();
	mBssSize = 0;
	mKernelCapabilities.clear();;
}

const std::string& nn::hac::KernelInitialProcessHeader::getName() const
{
	return mName;
}

void nn::hac::KernelInitialProcessHeader::setName(const std::string& name)
{
	mName = name;
}

uint64_t nn::hac::KernelInitialProcessHeader::getTitleId() const
{
	return mTitleId;
}

void nn::hac::KernelInitialProcessHeader::setTitleId(uint64_t title_id)
{
	mTitleId = title_id;
}

uint32_t nn::hac::KernelInitialProcessHeader::getVersion() const
{
	return mVersion;
}

void nn::hac::KernelInitialProcessHeader::setVersion(uint32_t version)
{
	mVersion = version;
}

bool nn::hac::KernelInitialProcessHeader::getIs64BitInstructionFlag() const
{
	return mIs64BitInstructionFlag;
}

void nn::hac::KernelInitialProcessHeader::setIs64BitInstructionFlag(bool flag)
{
	mIs64BitInstructionFlag = flag;
}

bool nn::hac::KernelInitialProcessHeader::getIs64BitAddressSpaceFlag() const
{
	return mIs64BitAddressSpaceFlag;
}

void nn::hac::KernelInitialProcessHeader::setIs64BitAddressSpaceFlag(bool flag)
{
	mIs64BitAddressSpaceFlag = flag;
}

bool nn::hac::KernelInitialProcessHeader::getUseSecureMemoryFlag() const
{
	return mUseSecureMemoryFlag;
}

void nn::hac::KernelInitialProcessHeader::setUseSecureMemoryFlag(bool flag)
{
	mUseSecureMemoryFlag = flag;
}

byte_t nn::hac::KernelInitialProcessHeader::getMainThreadPriority() const
{
	return mMainThreadPriority;
}

void nn::hac::KernelInitialProcessHeader::setMainThreadPriority(byte_t priority)
{
	mMainThreadPriority = priority;
}

byte_t nn::hac::KernelInitialProcessHeader::getMainThreadCpuId() const
{
	return mMainThreadCpuId;
}

void nn::hac::KernelInitialProcessHeader::setMainThreadCpuId(byte_t cpu_id)
{
	mMainThreadCpuId = cpu_id;
}

uint32_t nn::hac::KernelInitialProcessHeader::getMainThreadStackSize() const
{
	return mMainThreadStackSize;
}

void nn::hac::KernelInitialProcessHeader::setMainThreadStackSize(uint32_t size)
{
	mMainThreadStackSize = size;
}

const nn::hac::KernelInitialProcessHeader::sCodeSegment& nn::hac::KernelInitialProcessHeader::getTextSegmentInfo() const
{
	return mTextInfo;
}

void nn::hac::KernelInitialProcessHeader::setTextSegmentInfo(const sCodeSegment& info)
{
	mTextInfo = info;
}

const nn::hac::KernelInitialProcessHeader::sCodeSegment& nn::hac::KernelInitialProcessHeader::getRoSegmentInfo() const
{
	return mRoInfo;
}

void nn::hac::KernelInitialProcessHeader::setRoSegmentInfo(const sCodeSegment& info)
{
	mRoInfo = info;
}

const nn::hac::KernelInitialProcessHeader::sCodeSegment& nn::hac::KernelInitialProcessHeader::getDataSegmentInfo() const
{
	return mDataInfo;
}

void nn::hac::KernelInitialProcessHeader::setDataSegmentInfo(const sCodeSegment& info)
{
	mDataInfo = info;
}

uint32_t nn::hac::KernelInitialProcessHeader::getBssSize() const
{
	return mBssSize;
}

void nn::hac::KernelInitialProcessHeader::setBssSize(uint32_t size)
{
	mBssSize = size;
}

const nn::hac::KernelCapabilityControl& nn::hac::KernelInitialProcessHeader::getKernelCapabilities() const
{
	return mKernelCapabilities;
}

void nn::hac::KernelInitialProcessHeader::setKernelCapabilities(const KernelCapabilityControl& kc)
{
	mKernelCapabilities = kc;
}