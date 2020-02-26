#include <nn/hac/ApplicationControlPropertyUtil.h>
#include <sstream>
#include <iomanip>

bool nn::hac::ApplicationControlPropertyUtil::validateSaveDataSizeMax(int64_t size, int64_t alignment)
{
	return (alignment != 0 && (size & (alignment - 1)) != 0) == false;
}

bool nn::hac::ApplicationControlPropertyUtil::validateSaveDataSize(int64_t size)
{
	return (size & 0x3fff) == 0;
}
