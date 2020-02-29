#pragma once
#include <nn/hac/define/cnmt.h>
#include <string>

namespace nn
{
namespace hac
{
	class ContentMetaUtil
	{
	public:
		static std::string getContentTypeAsString(nn::hac::cnmt::ContentType val);
		static std::string getContentMetaTypeAsString(nn::hac::cnmt::ContentMetaType val);
		static std::string getUpdateTypeAsString(nn::hac::cnmt::UpdateType val);
		static std::string getContentMetaAttributeAsString(nn::hac::cnmt::ContentMetaAttribute val);

	private:
		const std::string kModuleName = "CONTENT_META_UTIL";
	};
}
}