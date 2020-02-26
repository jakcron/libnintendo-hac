#pragma once
#include <nn/hac/IKernelCapabilityHandler.h>

namespace nn
{
namespace hac
{
	class SystemCallHandler :
		public IKernelCapabilityHandler
	{
	public:
		static const uint32_t kMaxSystemCall = (BIT(3) * 24) - 1;

		SystemCallHandler();

		void operator=(const SystemCallHandler& other);
		bool operator==(const SystemCallHandler& other) const;
		bool operator!=(const SystemCallHandler& other) const;

		// kernel capabilty list in/out
		void importKernelCapabilityList(const fnd::List<KernelCapabilityEntry>& caps);
		void exportKernelCapabilityList(fnd::List<KernelCapabilityEntry>& caps) const;
		void clear();
		bool isSet() const;

		// variables
		const fnd::List<nn::hac::kc::SystemCall>& getSystemCalls() const;
		void setSystemCallList(const fnd::List<nn::hac::kc::SystemCall>& calls);

	private:
		const std::string kModuleName = "SYSTEM_CALL_HANDLER";
		static const size_t kSyscallTotalEntryNum = (kMaxSystemCall / 24) + 1;

		bool mIsSet;
		fnd::List<nn::hac::kc::SystemCall> mSystemCalls;
	};
}
}
