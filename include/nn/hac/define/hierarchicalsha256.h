#pragma once
#include <nn/hac/define/types.h>

namespace nn
{
namespace hac
{
	namespace hierarchicalsha256
	{
		static const size_t kDefaultLayerNum = 2;
		static const size_t kMaxLayerNum = 2;
	}
	
#pragma pack(push,1)
	struct sHierarchicalSha256Header
	{
		detail::sha256_hash_t master_hash;
		tc::bn::le32<uint32_t> hash_block_size;
		tc::bn::le32<uint32_t> layer_num;
		struct sLayer
		{
			tc::bn::le64<int64_t> offset;
			tc::bn::le64<int64_t> size;
		} layer[hierarchicalsha256::kMaxLayerNum];
	};
	static_assert(sizeof(sHierarchicalSha256Header) == 0x48, "sHierarchicalSha256Header size.");
#pragma pack(pop)
}
}