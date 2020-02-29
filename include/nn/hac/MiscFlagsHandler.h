#pragma once
#include <nn/hac/IKernelCapabilityHandler.h>
#include <nn/hac/MiscFlagsEntry.h>

namespace nn
{
namespace hac
{
	class MiscFlagsHandler :
		public IKernelCapabilityHandler
	{
	public:
		MiscFlagsHandler();

		void operator=(const MiscFlagsHandler& other);
		bool operator==(const MiscFlagsHandler& other) const;
		bool operator!=(const MiscFlagsHandler& other) const;

		// kernel capabilty list in/out
		void importKernelCapabilityList(const fnd::List<KernelCapabilityEntry>& caps);
		void exportKernelCapabilityList(fnd::List<KernelCapabilityEntry>& caps) const;
		void clear();
		bool isSet() const;

		// variables
		const fnd::List<nn::hac::kc::MiscFlags>& getFlagList() const;
		void setFlagList(fnd::List<nn::hac::kc::MiscFlags> flags);

	private:
		const std::string kModuleName = "MISC_FLAGS_HANDLER";
		static const size_t kMaxKernelCapNum = 1;

		bool mIsSet;
		fnd::List<nn::hac::kc::MiscFlags> mFlags;
	};
}
}