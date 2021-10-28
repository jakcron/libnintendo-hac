#pragma once
#include <nn/hac/define/bktr.h>

#include <tc/ArgumentNullException.h>
#include <tc/ArgumentOutOfRangeException.h>
#include <tc/InvalidOperationException.h>

namespace nn { namespace hac {

class BucketTree
{
public:
	using sNodeHeader = sBucketTreeNodeHeader;
	static const size_t kNodeSizeMin = bktr::kNodeSizeMin;
	static const size_t kNodeSizeMax = bktr::kNodeSizeMax;

	BucketTree();

	void parse(const std::shared_ptr<tc::io::IStream>& table_stream, size_t node_size, size_t entry_size, size_t entry_count);
private:
	static size_t divideUp(size_t numerator, size_t denominator)
	{
		return (numerator / denominator) + ((numerator % denominator > 0) ? 1 : 0);
	}
	
	static bool isPowerOfTwo(size_t val)
	{
		return (val & (val - 1)) == 0;
	}

	static size_t getNodeEntryCapacity(size_t node_size, size_t entry_size)
	{
		return node_size / entry_size;
	}

	static size_t getNodeOffsetCapacity(size_t node_size)
	{
		return getNodeEntryCapacity(node_size, sizeof(int64_t));
	}

	static size_t getL2NodeCount(size_t node_size, size_t entry_size, size_t entry_count)
	{
		const size_t offset_count_per_node = getNodeOffsetCapacity(node_size); // how many offsets can be stored in a node 
		const size_t entry_set_count       = getEntrySetCount(node_size, entry_size, entry_count);  // how many nodes are needed to store the entries

		// if there are less entry sets than offsets storable in a node, then there needs not be any L2 nodes
		if (entry_set_count <= offset_count_per_node)
		{ 
			return 0;
		}

		// determine l2 node count by determining how many nodes are required to refer to the entry sets (based on the node offset capacity)
		const size_t node_l2_count = divideUp(entry_set_count, offset_count_per_node);

		// node_l2_count cannot exceed offset_count_per_node, because the l2 nodes are indexed in the l1 node. And there are no l3 nodes
		if (node_l2_count > offset_count_per_node)
		{
			throw tc::InvalidOperationException("BucketTree::getL2NodeCount()", "Too many entries in BucketTree.");
		}

		// ???
		return divideUp(entry_set_count - (offset_count_per_node - (node_l2_count - 1)), offset_count_per_node);
	};

	static size_t getEntrySetCount(size_t node_size, size_t entry_size, size_t entry_count)
	{
		return divideUp(getNodeEntryCapacity(node_size, entry_size), entry_count);
	}

	static int64_t getNodeStorageSize(size_t node_size, size_t entry_size, size_t entry_count)
	{
		// (l1 node (1) + l2 nodes (0 or more)) * node_size
		return (1 + getL2NodeCount(entry_count, node_size, entry_size)) * node_size;
	}

	static int64_t geEntrySetStorageSize(size_t node_size, size_t entry_size, size_t entry_count)
	{
		return getEntrySetCount(entry_count, node_size, entry_size) * node_size;
	}


private:
	std::string mModuleName;

	size_t mEntryCount;
	size_t mNodeSize;
	size_t mEntrySize;

	//std::list<>
};

}} // namespace nn::hac