#pragma once
#include <cstring>
#include <nn/hac/define/nro.h>
#include <fnd/IByteModel.h>
#include <fnd/List.h>

namespace nn
{
namespace hac
{
	class NroHeader :
		public fnd::IByteModel
	{
	public:
		struct sModuleId
		{
			byte_t data[nro::kModuleIdSize];

			void operator=(const sModuleId& other)
			{
				memcpy(data, other.data, nro::kModuleIdSize);
			}

			bool operator==(const sModuleId& other) const
			{
				return memcmp(data, other.data, nro::kModuleIdSize) == 0;
			}

			bool operator!=(const sModuleId& other) const
			{
				return !(*this == other);
			}
		};

		struct sSection
		{
			uint32_t memory_offset;
			uint32_t size;

			void operator=(const sSection& other)
			{
				memory_offset = other.memory_offset;
				size = other.size;
			}

			bool operator==(const sSection& other) const
			{
				return (memory_offset == other.memory_offset) \
					&& (size == other.size);
			}

			bool operator!=(const sSection& other) const
			{
				return !(*this == other);
			}
		};

		NroHeader();
		NroHeader(const NroHeader& other);

		void operator=(const NroHeader& other);
		bool operator==(const NroHeader& other) const;
		bool operator!=(const NroHeader& other) const;

		// IByteModel
		void toBytes();
		void fromBytes(const byte_t* bytes, size_t len);
		const fnd::Vec<byte_t>& getBytes() const;

		// variables
		void clear();

		uint32_t getRoCrtEntryPoint() const;
		void setRoCrtEntryPoint(uint32_t addr);

		uint32_t getRoCrtModOffset() const;
		void setRoCrtModOffset(uint32_t mod_offset);

		uint32_t getNroSize() const;
		void setNroSize(uint32_t size);

		const sSection& getTextInfo() const;
		void setTextInfo(const sSection& info);

		const sSection& getRoInfo() const;
		void setRoInfo(const sSection& info);

		const sSection& getDataInfo() const;
		void setDataInfo(const sSection& info);

		uint32_t getBssSize() const;
		void setBssSize(uint32_t size);

		const sModuleId& getModuleId() const;
		void setModuleId(const sModuleId& id);

		const sSection& getRoEmbeddedInfo() const;
		void setRoEmbeddedInfo(const sSection& info);

		const sSection& getRoDynStrInfo() const;
		void setRoDynStrInfo(const sSection& info);

		const sSection& getRoDynSymInfo() const;
		void setRoDynSymInfo(const sSection& info);
	private:
		const std::string kModuleName = "NRO_HEADER";

		// binary
		fnd::Vec<byte_t> mRawBinary;

		// data
		uint32_t mRoCrtEntryPoint;
		uint32_t mRoCrtModOffset;
		uint32_t mNroSize;
		sSection mTextInfo;
		sSection mRoInfo;
		sSection mDataInfo;
		uint32_t mBssSize;
		sModuleId mModuleId;
		sSection mRoEmbeddedInfo;
		sSection mRoDynStrInfo;
		sSection mRoDynSymInfo;
	};
}
}