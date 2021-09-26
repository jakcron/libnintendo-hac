#pragma once
#include <nn/hac/define/fac.h>

namespace nn
{
namespace hac
{
	class FileSystemAccessControl
	{
	public:
		struct sSaveDataOwnerId
		{
			nn::hac::fac::SaveDataOwnerIdAccessType access_type;
			uint64_t id;

			void operator=(const sSaveDataOwnerId& other)
			{
				access_type = other.access_type;
				id = other.id;
			}

			bool operator==(const sSaveDataOwnerId& other) const
			{
				return (access_type == other.access_type) \
					&& (id == other.id);
			}

			bool operator!=(const sSaveDataOwnerId& other) const
			{
				return !(*this == other);
			}
		}; 

		FileSystemAccessControl();
		FileSystemAccessControl(const FileSystemAccessControl& other);

		void operator=(const FileSystemAccessControl& other);
		bool operator==(const FileSystemAccessControl& other) const;
		bool operator!=(const FileSystemAccessControl& other) const;

		// IByteModel
		void toBytes();
		void fromBytes(const byte_t* data, size_t len);
		const tc::ByteData& getBytes() const;

		// variables
		void clear();

		uint32_t getFormatVersion() const;
		void setFormatVersion(uint32_t version);

		const std::vector<nn::hac::fac::FsAccessFlag>& getFsAccess() const;
		void setFsAccess(const std::vector<nn::hac::fac::FsAccessFlag>& access);

		const std::vector<uint64_t>& getContentOwnerIdList() const;
		void setContentOwnerIdList(const std::vector<uint64_t>& list);

		const std::vector<sSaveDataOwnerId>& getSaveDataOwnerIdList() const;
		void setSaveDataOwnerIdList(const std::vector<sSaveDataOwnerId>& list);
	private:
		const std::string kModuleName = "FILE_SYSTEM_ACCESS_CONTROL";

		// raw data
		tc::ByteData mRawBinary;

		// variables
		uint32_t mVersion;
		std::vector<nn::hac::fac::FsAccessFlag> mFsAccess;
		std::vector<uint64_t> mContentOwnerIdList;
		std::vector<sSaveDataOwnerId> mSaveDataOwnerIdList;
	};
}
}