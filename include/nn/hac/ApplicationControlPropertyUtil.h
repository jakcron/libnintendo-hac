#pragma once
#include <nn/hac/define/nacp.h>

namespace nn
{
namespace hac
{
	class ApplicationControlPropertyUtil
	{
	public:
		static bool validateSaveDataSizeMax(int64_t size, int64_t alignment);
		static bool validateSaveDataSize(int64_t size);
	};
}
}