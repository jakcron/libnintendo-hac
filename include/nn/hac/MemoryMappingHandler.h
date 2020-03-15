#pragma once
#include <nn/hac/IKernelCapabilityHandler.h>

namespace nn
{
namespace hac
{
	class MemoryMappingHandler :
		public IKernelCapabilityHandler
	{
	public:
		struct sMemoryMapping
		{
			uint32_t addr; // page index
			uint32_t size; // page num
			kc::MemoryPermission perm;
			kc::MappingType type;

			bool operator==(const sMemoryMapping& other) const
			{
				return (addr == other.addr) \
					&& (size == other.size) \
					&& (perm == other.perm) \
					&& (type == other.type);
			}

			bool operator!=(const sMemoryMapping& other) const
			{
				return !operator==(other);
			}

			const sMemoryMapping& operator=(const sMemoryMapping& other)
			{
				addr = other.addr;
				size = other.size;
				perm = other.perm;
				type = other.type;

				return *this;
			}
		};

		MemoryMappingHandler();

		void operator=(const MemoryMappingHandler& other);
		bool operator==(const MemoryMappingHandler& other) const;
		bool operator!=(const MemoryMappingHandler& other) const;

		// kernel capabilty list in/out
		void importKernelCapabilityList(const fnd::List<KernelCapabilityEntry>& caps);
		void exportKernelCapabilityList(fnd::List<KernelCapabilityEntry>& caps) const;
		void clear();
		bool isSet() const;

		const fnd::List<sMemoryMapping>& getMemoryMaps() const;
		const fnd::List<sMemoryMapping>& getIoMemoryMaps() const;

	private:
		const std::string kModuleName = "MEMORY_MAPPING_HANDLER";
		static const uint32_t kMaxPageAddr = _BIT(24) - 1;
		static const uint32_t kMaxPageNum = _BIT(20) - 1;

		bool mIsSet;
		fnd::List<sMemoryMapping> mMemRange;
		fnd::List<sMemoryMapping> mMemPage;
	};
}
}