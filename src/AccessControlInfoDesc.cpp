#include <nn/hac/AccessControlInfoDesc.h>

nn::hac::AccessControlInfoDesc::AccessControlInfoDesc()
{
	clear();
}

nn::hac::AccessControlInfoDesc::AccessControlInfoDesc(const AccessControlInfoDesc & other)
{
	*this = other;
}

void nn::hac::AccessControlInfoDesc::operator=(const AccessControlInfoDesc & other)
{
	mRawBinary = other.mRawBinary;
	mContentArchiveHeaderSignature2Key = other.mContentArchiveHeaderSignature2Key;
	mProductionFlag = other.mProductionFlag;
	mUnqualifiedApprovalFlag = other.mUnqualifiedApprovalFlag;
	mMemoryRegion = other.mMemoryRegion;
	mProgramIdRestrict = other.mProgramIdRestrict;
	mFileSystemAccessControl = other.mFileSystemAccessControl;
	mServiceAccessControl = other.mServiceAccessControl;
	mKernelCapabilities = other.mKernelCapabilities;
}

bool nn::hac::AccessControlInfoDesc::operator==(const AccessControlInfoDesc & other) const
{
	return (mContentArchiveHeaderSignature2Key == other.mContentArchiveHeaderSignature2Key) \
		&& (mProductionFlag == other.mProductionFlag) \
		&& (mUnqualifiedApprovalFlag == other.mUnqualifiedApprovalFlag) \
		&& (mMemoryRegion == other.mMemoryRegion) \
		&& (mProgramIdRestrict == other.mProgramIdRestrict) \
		&& (mFileSystemAccessControl == other.mFileSystemAccessControl) \
		&& (mServiceAccessControl == other.mServiceAccessControl) \
		&& (mKernelCapabilities == other.mKernelCapabilities);
}

bool nn::hac::AccessControlInfoDesc::operator!=(const AccessControlInfoDesc & other) const
{
	return !(*this == other);
}

void nn::hac::AccessControlInfoDesc::toBytes()
{
	// serialise the sections
	mFileSystemAccessControl.toBytes();
	mServiceAccessControl.toBytes();
	mKernelCapabilities.toBytes();

	// determine section layout
	struct sLayout {
		uint32_t offset, size;
	} fac, sac, kc;

	fac.offset = (uint32_t)align(sizeof(sAciDescHeader), aci::kSectionAlignSize);
	fac.size = (uint32_t)mFileSystemAccessControl.getBytes().size();
	sac.offset = (uint32_t)align(fac.offset + fac.size, aci::kSectionAlignSize);
	sac.size = (uint32_t)mServiceAccessControl.getBytes().size();
	kc.offset = (uint32_t)align(sac.offset + sac.size, aci::kSectionAlignSize);
	kc.size = (uint32_t)mKernelCapabilities.getBytes().size();

	// get total size
	size_t total_size = _MAX(_MAX(fac.offset + fac.size, sac.offset + sac.size), kc.offset + kc.size); 

	mRawBinary.alloc(total_size);
	sAciDescHeader* hdr = (sAciDescHeader*)mRawBinary.data();

	// set rsa modulus
	memcpy(hdr->nca_rsa_signature2_modulus, mContentArchiveHeaderSignature2Key.modulus, fnd::rsa::kRsa2048Size);

	// set type
	hdr->st_magic = aci::kAciDescStructMagic;

	// set "acid size"
	hdr->signed_size = (uint32_t)(total_size - fnd::rsa::kRsa2048Size);

	// set flags
	sAciDescHeaderFlag flags;
	flags.production = mProductionFlag;
	flags.unqualified_approval = mUnqualifiedApprovalFlag;
	flags.memory_region = (byte_t)mMemoryRegion;
	hdr->flags = flags.raw;

	// set program id restrict settings
	hdr->program_id_min = mProgramIdRestrict.min;
	hdr->program_id_max = mProgramIdRestrict.max;

	// set offset/size
	hdr->fac.offset = fac.offset;
	hdr->fac.size = fac.size;
	hdr->sac.offset = sac.offset;
	hdr->sac.size = sac.size;
	hdr->kc.offset = kc.offset;
	hdr->kc.size = kc.size;

	// write data
	memcpy(mRawBinary.data() + fac.offset, mFileSystemAccessControl.getBytes().data(), fac.size);
	memcpy(mRawBinary.data() + sac.offset, mServiceAccessControl.getBytes().data(), sac.size);
	memcpy(mRawBinary.data() + kc.offset, mKernelCapabilities.getBytes().data(), kc.size);
}

void nn::hac::AccessControlInfoDesc::fromBytes(const byte_t* data, size_t len)
{
	// check size
	if (len < sizeof(sAciDescHeader))
	{
		throw fnd::Exception(kModuleName, "AccessControlInfoDesc binary is too small");
	}
	
	// clear variables
	clear();

	// save a copy of the header
	sAciDescHeader hdr;
	memcpy((void*)&hdr, data, sizeof(sAciDescHeader));

	// check magic
	if (hdr.st_magic.get() != aci::kAciDescStructMagic)
	{
		throw fnd::Exception(kModuleName, "AccessControlInfoDesc header corrupt");
	}
	
	// get total size
	size_t total_size = _MAX(_MAX(hdr.fac.offset.get() + hdr.fac.size.get(), hdr.sac.offset.get() + hdr.sac.size.get()), hdr.kc.offset.get() + hdr.kc.size.get()); 

	// validate binary size
	if (len < total_size)
	{
		throw fnd::Exception(kModuleName, "AccessControlInfoDesc binary is too small");
	}

	// allocate memory for header
	mRawBinary.alloc(total_size);
	memcpy(mRawBinary.data(), data, mRawBinary.size());

	// save variables
	memcpy(mContentArchiveHeaderSignature2Key.modulus, hdr.nca_rsa_signature2_modulus, fnd::rsa::kRsa2048Size);

	// acid flags
	sAciDescHeaderFlag flags;
	flags.raw = hdr.flags.get();
	mProductionFlag = flags.production;
	mUnqualifiedApprovalFlag = flags.unqualified_approval;
	mMemoryRegion = aci::MemoryRegion(flags.memory_region);

	// program id
	mProgramIdRestrict.min = hdr.program_id_min.get();
	mProgramIdRestrict.max = hdr.program_id_max.get();

	// fac,sac,kc
	mFileSystemAccessControl.fromBytes(mRawBinary.data() + hdr.fac.offset.get(), hdr.fac.size.get());
	mServiceAccessControl.fromBytes(mRawBinary.data() + hdr.sac.offset.get(), hdr.sac.size.get());
	mKernelCapabilities.fromBytes(mRawBinary.data() + hdr.kc.offset.get(), hdr.kc.size.get());
}

const fnd::Vec<byte_t>& nn::hac::AccessControlInfoDesc::getBytes() const
{
	return mRawBinary;
}

void nn::hac::AccessControlInfoDesc::generateSignature(const fnd::rsa::sRsa2048Key& key)
{
	if (mRawBinary.size() == 0)
		toBytes();

	byte_t hash[fnd::sha::kSha256HashLen];
	fnd::sha::Sha256(mRawBinary.data() + fnd::rsa::kRsa2048Size, mRawBinary.size() - fnd::rsa::kRsa2048Size, hash);

	if (fnd::rsa::pss::rsaSign(key, fnd::sha::HASH_SHA256, hash, mRawBinary.data()) != 0)
	{
		throw fnd::Exception(kModuleName, "Failed to sign Access Control Info Desc");
	}
}

void nn::hac::AccessControlInfoDesc::validateSignature(const fnd::rsa::sRsa2048Key& key) const
{
	if (mRawBinary.size() == 0)
		throw fnd::Exception(kModuleName, "No Access Control Info Desc binary exists to verify");

	byte_t hash[fnd::sha::kSha256HashLen];
	fnd::sha::Sha256(mRawBinary.data() + fnd::rsa::kRsa2048Size, mRawBinary.size() - fnd::rsa::kRsa2048Size, hash);

	if (fnd::rsa::pss::rsaVerify(key, fnd::sha::HASH_SHA256, hash, mRawBinary.data()) != 0)
	{
		throw fnd::Exception(kModuleName, "Failed to verify Access Control Info Desc");
	}
}

void nn::hac::AccessControlInfoDesc::clear()
{
	mRawBinary.clear();
	memset((void*)&mContentArchiveHeaderSignature2Key, 0, sizeof(mContentArchiveHeaderSignature2Key));
	mProductionFlag = false;
	mUnqualifiedApprovalFlag = false;
	mMemoryRegion = aci::MemoryRegion::Application;
	mProgramIdRestrict.min = 0;
	mProgramIdRestrict.max = 0;
	mFileSystemAccessControl.clear();
	mServiceAccessControl.clear();
	mKernelCapabilities.clear();
}

const fnd::rsa::sRsa2048Key& nn::hac::AccessControlInfoDesc::getContentArchiveHeaderSignature2Key() const
{
	return mContentArchiveHeaderSignature2Key;
}

void nn::hac::AccessControlInfoDesc::setContentArchiveHeaderSignature2Key(const fnd::rsa::sRsa2048Key& key)
{
	mContentArchiveHeaderSignature2Key = key;
}

bool nn::hac::AccessControlInfoDesc::getProductionFlag() const
{
	return mProductionFlag;
}

void nn::hac::AccessControlInfoDesc::setProductionFlag(bool flag)
{
	mProductionFlag = flag;
}

bool nn::hac::AccessControlInfoDesc::getUnqualifiedApprovalFlag() const
{
	return mUnqualifiedApprovalFlag;
}

void nn::hac::AccessControlInfoDesc::setUnqualifiedApprovalFlag(bool flag)
{
	mUnqualifiedApprovalFlag = flag;
}

nn::hac::aci::MemoryRegion nn::hac::AccessControlInfoDesc::getMemoryRegion() const
{
	return mMemoryRegion;
}

void nn::hac::AccessControlInfoDesc::setMemoryRegion(nn::hac::aci::MemoryRegion memory_region)
{
	mMemoryRegion = memory_region;
}

const nn::hac::AccessControlInfoDesc::sProgramIdRestrict&  nn::hac::AccessControlInfoDesc::getProgramIdRestrict() const
{
	return mProgramIdRestrict;
}

void nn::hac::AccessControlInfoDesc::setProgramIdRestrict(const sProgramIdRestrict& pid_restrict)
{
	mProgramIdRestrict = pid_restrict;
}

const nn::hac::FileSystemAccessControl& nn::hac::AccessControlInfoDesc::getFileSystemAccessControl() const
{
	return mFileSystemAccessControl;
}

void nn::hac::AccessControlInfoDesc::setFileSystemAccessControl(const nn::hac::FileSystemAccessControl& fac)
{
	mFileSystemAccessControl = fac;
}

const nn::hac::ServiceAccessControl& nn::hac::AccessControlInfoDesc::getServiceAccessControl() const
{
	return mServiceAccessControl;
}

void nn::hac::AccessControlInfoDesc::setServiceAccessControl(const nn::hac::ServiceAccessControl& sac)
{
	mServiceAccessControl = sac;
}

const nn::hac::KernelCapabilityControl& nn::hac::AccessControlInfoDesc::getKernelCapabilities() const
{
	return mKernelCapabilities;
}

void nn::hac::AccessControlInfoDesc::setKernelCapabilities(const nn::hac::KernelCapabilityControl& kc)
{
	mKernelCapabilities = kc;
}