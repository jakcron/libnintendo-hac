#include <nn/hac/MiscParamsHandler.h>

nn::hac::MiscParamsHandler::MiscParamsHandler() :
	mIsSet(false),
	mEntry()
{}

void nn::hac::MiscParamsHandler::operator=(const MiscParamsHandler & other)
{
	mIsSet = other.mIsSet;
	mEntry.setKernelCapability(other.mEntry.getKernelCapability());
}

bool nn::hac::MiscParamsHandler::operator==(const MiscParamsHandler & other) const
{
	return (mIsSet == other.mIsSet) \
		&& (mEntry.getKernelCapability() == other.mEntry.getKernelCapability());
}

bool nn::hac::MiscParamsHandler::operator!=(const MiscParamsHandler & other) const
{
	return !(*this == other);
}

void nn::hac::MiscParamsHandler::importKernelCapabilityList(const fnd::List<KernelCapabilityEntry>& caps)
{
	if (caps.size() > kMaxKernelCapNum)
	{
		throw fnd::Exception(kModuleName, "Too many kernel capabilities");
	}

	if (caps.size() == 0)
		return;

	mEntry.setKernelCapability(caps[0]);

	mIsSet = true;
}

void nn::hac::MiscParamsHandler::exportKernelCapabilityList(fnd::List<KernelCapabilityEntry>& caps) const
{
	if (isSet() == false)
		return;

	caps.addElement(mEntry.getKernelCapability());
}

void nn::hac::MiscParamsHandler::clear()
{
	mIsSet = false;
	mEntry = MiscParamsEntry();
}

bool nn::hac::MiscParamsHandler::isSet() const
{
	return mIsSet;
}

nn::hac::kc::ProgramType nn::hac::MiscParamsHandler::getProgramType() const
{
	return mEntry.getProgramType();
}

void nn::hac::MiscParamsHandler::setProgramType(nn::hac::kc::ProgramType type)
{
	mEntry.setProgramType(type);
	mIsSet = true;
}