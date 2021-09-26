#pragma once
#include <nn/hac/define/ini.h>

namespace nn
{
namespace hac
{
	class IniHeader
	{
	public:
		IniHeader();
		IniHeader(const IniHeader& other);

		void operator=(const IniHeader& other);
		bool operator==(const IniHeader& other) const;
		bool operator!=(const IniHeader& other) const;

		// IByteModel
		void toBytes();
		void fromBytes(const byte_t* data, size_t len);
		const tc::ByteData& getBytes() const;

		// variables
		void clear();

		uint32_t getSize() const;
		void setSize(uint32_t size);

		uint32_t getKipNum() const;
		void setKipNum(uint32_t num);
	private:
		const std::string kModuleName = "INI_HEADER";

		// raw binary
		tc::ByteData mRawBinary;

		// variables
		uint32_t mSize;
		uint32_t mKipNum;
	};
}
}