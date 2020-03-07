#include <nn/hac/Meta.h>

#include <fnd/SimpleTextOutput.h>

nn::hac::Meta::Meta()
{
	clear();
}

nn::hac::Meta::Meta(const Meta & other) :
	Meta()
{
	*this = other;
}

void nn::hac::Meta::operator=(const Meta & other)
{
	mRawBinary = other.mRawBinary;
	mAccessControlInfoDescKeyGeneration = other.mAccessControlInfoDescKeyGeneration;
	mIs64BitInstructionFlag = other.mIs64BitInstructionFlag;
	mProcessAddressSpace = other.mProcessAddressSpace;
	mOptimizeMemoryAllocationFlag = other.mOptimizeMemoryAllocationFlag;
	mMainThreadPriority = other.mMainThreadPriority;
	mMainThreadCpuId = other.mMainThreadCpuId;
	mVersion = other.mVersion;
	mMainThreadStackSize = other.mMainThreadStackSize;
	mName = other.mName;
	mProductCode = other.mProductCode;
	mAccessControlInfo = other.mAccessControlInfo;
	mAccessControlInfoDesc = other.mAccessControlInfoDesc;
}

bool nn::hac::Meta::operator==(const Meta & other) const
{
	return (mAccessControlInfoDescKeyGeneration == other.mAccessControlInfoDescKeyGeneration) \
		&& (mIs64BitInstructionFlag == other.mIs64BitInstructionFlag) \
		&& (mProcessAddressSpace == other.mProcessAddressSpace) \
		&& (mOptimizeMemoryAllocationFlag == other.mOptimizeMemoryAllocationFlag) \
		&& (mMainThreadPriority == other.mMainThreadPriority) \
		&& (mMainThreadCpuId == other.mMainThreadCpuId) \
		&& (mVersion == other.mVersion) \
		&& (mMainThreadStackSize == other.mMainThreadStackSize) \
		&& (mName == other.mName) \
		&& (mProductCode == other.mProductCode) \
		&& (mAccessControlInfo == other.mAccessControlInfo) \
		&& (mAccessControlInfoDesc == other.mAccessControlInfoDesc);
}

bool nn::hac::Meta::operator!=(const Meta & other) const
{
	return !(*this == other);
}

void nn::hac::Meta::toBytes()
{
	if (mAccessControlInfoDesc.getBytes().size() == 0)
		mAccessControlInfoDesc.toBytes();

	if (mAccessControlInfo.getBytes().size() == 0)
		mAccessControlInfo.toBytes();


	// determine section layout
	struct sLayout {
		uint32_t offset, size;
	} acid, aci;

	acid.offset = (uint32_t)align(sizeof(sMetaHeader), meta::kSectionAlignSize);
	acid.size = (uint32_t)mAccessControlInfoDesc.getBytes().size();
	aci.offset = (uint32_t)(acid.offset + align(acid.size, meta::kSectionAlignSize));
	aci.size = (uint32_t)mAccessControlInfo.getBytes().size();
	

	// get total size
	size_t total_size = _MAX(_MAX(acid.offset + acid.size, aci.offset + aci.size), align(sizeof(sMetaHeader), meta::kSectionAlignSize)); 

	mRawBinary.alloc(total_size);
	sMetaHeader* hdr = (sMetaHeader*)mRawBinary.data();

	// set type
	hdr->st_magic = meta::kMetaStructMagic;

	// set variables
	hdr->aci_desc_key_generation = mAccessControlInfoDescKeyGeneration;
	hdr->flag.is_64bit_instruction = mIs64BitInstructionFlag;
	hdr->flag.process_address_space = (byte_t)mProcessAddressSpace;
	hdr->flag.optimise_memory_allocation = mOptimizeMemoryAllocationFlag;
	hdr->main_thread_priority = mMainThreadPriority;
	hdr->main_thread_cpu_id = mMainThreadCpuId;
	hdr->version = mVersion;
	hdr->main_thread_stack_size = mMainThreadStackSize;
	strncpy(hdr->name, mName.c_str(), meta::kNameMaxLen);
	strncpy(hdr->product_code, mProductCode.c_str(), meta::kProductCodeMaxLen);

	// set offset/size
	hdr->aci.offset = aci.offset;
	hdr->aci.size = aci.size;
	hdr->aci_desc.offset = acid.offset;
	hdr->aci_desc.size = acid.size;

	// write aci & acid
	if (mAccessControlInfo.getBytes().size() > 0)
	{
		memcpy(mRawBinary.data() + aci.offset, mAccessControlInfo.getBytes().data(), mAccessControlInfo.getBytes().size());
	}
	if (mAccessControlInfoDesc.getBytes().size() > 0)
	{
		memcpy(mRawBinary.data() + acid.offset, mAccessControlInfoDesc.getBytes().data(), mAccessControlInfoDesc.getBytes().size());
	}
}

void nn::hac::Meta::fromBytes(const byte_t* data, size_t len)
{
	// check size
	if (len < sizeof(sMetaHeader))
	{
		throw fnd::Exception(kModuleName, "META binary is too small");
	}
	
	// clear variables
	clear();

	// save a copy of the header
	sMetaHeader hdr;
	memcpy((void*)&hdr, data, sizeof(sMetaHeader));

	// check magic
	if (hdr.st_magic.get() != meta::kMetaStructMagic)
	{
		throw fnd::Exception(kModuleName, "META header corrupt (unrecognised struct signature)");
	}

	// save variables
	mAccessControlInfoDescKeyGeneration = hdr.aci_desc_key_generation;
	mIs64BitInstructionFlag = hdr.flag.is_64bit_instruction;
	mProcessAddressSpace = meta::ProcessAddressSpace(hdr.flag.process_address_space);
	mOptimizeMemoryAllocationFlag = hdr.flag.optimise_memory_allocation;
	mMainThreadPriority = hdr.main_thread_priority;
	mMainThreadCpuId = hdr.main_thread_cpu_id;
	mVersion = hdr.version.get();
	mMainThreadStackSize = hdr.main_thread_stack_size.get();
	mName = std::string(hdr.name, _MIN(strlen(hdr.name), meta::kNameMaxLen));
	mProductCode = std::string(hdr.product_code, _MIN(strlen(hdr.product_code), meta::kProductCodeMaxLen));

	// total size
	size_t total_size = _MAX(_MAX(hdr.aci_desc.offset.get() + hdr.aci_desc.size.get(), hdr.aci.offset.get() + hdr.aci.size.get()), sizeof(sMetaHeader));

	// check size
	if (total_size > len)
	{
		throw fnd::Exception(kModuleName, "META binary too small");
	}

	// save local copy
	mRawBinary.alloc(total_size);
	memcpy(mRawBinary.data(), data, mRawBinary.size());

	// import AccessControlInfo/AccessControlInfoDesc
	if (hdr.aci.size.get())
	{
		mAccessControlInfo.fromBytes(mRawBinary.data() + hdr.aci.offset.get(), hdr.aci.size.get());
	}
	if (hdr.aci_desc.size.get())
	{
		mAccessControlInfoDesc.fromBytes(mRawBinary.data() + hdr.aci_desc.offset.get(), hdr.aci_desc.size.get());
	}	
}

const fnd::Vec<byte_t>& nn::hac::Meta::getBytes() const
{
	return mRawBinary;
}

void nn::hac::Meta::clear()
{
	mRawBinary.clear();
	mAccessControlInfoDescKeyGeneration = 0;
	mIs64BitInstructionFlag = false;
	mProcessAddressSpace = meta::ProcessAddressSpace(0);
	mOptimizeMemoryAllocationFlag = false;
	mMainThreadPriority = 0;
	mMainThreadCpuId = 0;
	mVersion = 0;
	mMainThreadStackSize = 0;
	mName.clear();
	mProductCode.clear();
	mAccessControlInfo.clear();
	mAccessControlInfoDesc.clear();
}

byte_t nn::hac::Meta::getAccessControlInfoDescKeyGeneration() const
{
	return mAccessControlInfoDescKeyGeneration;
}

void nn::hac::Meta::setAccessControlInfoDescKeyGeneration(byte_t key_generation)
{
	mAccessControlInfoDescKeyGeneration = key_generation;
}

bool nn::hac::Meta::getIs64BitInstructionFlag() const
{
	return mIs64BitInstructionFlag;
}

void nn::hac::Meta::setIs64BitInstructionFlag(bool flag)
{
	mIs64BitInstructionFlag = flag;
}

nn::hac::meta::ProcessAddressSpace nn::hac::Meta::getProcessAddressSpace() const
{
	return mProcessAddressSpace;
}

void nn::hac::Meta::setProcessAddressSpace(meta::ProcessAddressSpace type)
{
	mProcessAddressSpace = type;
}

bool nn::hac::Meta::getOptimizeMemoryAllocationFlag() const
{
	return mOptimizeMemoryAllocationFlag;
}

void nn::hac::Meta::setOptimizeMemoryAllocationFlag(bool flag)
{
	mOptimizeMemoryAllocationFlag = flag;
}

byte_t nn::hac::Meta::getMainThreadPriority() const
{
	return mMainThreadPriority;
}

void nn::hac::Meta::setMainThreadPriority(byte_t priority)
{
	if (priority > meta::kMaxPriority)
	{
		throw fnd::Exception(kModuleName, "Illegal main thread priority (range 0-63)");
	}

	mMainThreadPriority = priority;
}

byte_t nn::hac::Meta::getMainThreadCpuId() const
{
	return mMainThreadCpuId;
}

void nn::hac::Meta::setMainThreadCpuId(byte_t core_num)
{
	mMainThreadCpuId = core_num;
}

uint32_t nn::hac::Meta::getVersion() const
{
	return mVersion;
}

void nn::hac::Meta::setVersion(uint32_t version)
{
	mVersion = version;
}

uint32_t nn::hac::Meta::getMainThreadStackSize() const
{
	return mMainThreadStackSize;
}

void nn::hac::Meta::setMainThreadStackSize(uint32_t size)
{
	mMainThreadStackSize = size;
}

const std::string & nn::hac::Meta::getName() const
{
	return mName;
}

void nn::hac::Meta::setName(const std::string & name)
{
	if (name.length() > meta::kNameMaxLen)
	{
		throw fnd::Exception(kModuleName, "Name is too long");
	}

	mName = name;
}

const std::string & nn::hac::Meta::getProductCode() const
{
	return mProductCode;
}

void nn::hac::Meta::setProductCode(const std::string & product_code)
{
	if (product_code.length() > meta::kProductCodeMaxLen)
	{
		throw fnd::Exception(kModuleName, "Product Code is too long");
	}

	mProductCode = product_code;
}

const nn::hac::AccessControlInfo & nn::hac::Meta::getAccessControlInfo() const
{
	return mAccessControlInfo;
}

void nn::hac::Meta::setAccessControlInfo(const AccessControlInfo & aci)
{
	mAccessControlInfo = aci;
}

const nn::hac::AccessControlInfoDesc & nn::hac::Meta::getAccessControlInfoDesc() const
{
	return mAccessControlInfoDesc;
}

void nn::hac::Meta::setAccessControlInfoDesc(const AccessControlInfoDesc & aci_desc)
{
	mAccessControlInfoDesc = aci_desc;
}