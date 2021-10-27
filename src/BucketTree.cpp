#include <nn/hac/BucketTree.h>

nn::hac::BucketTree::BucketTree() :
	mModuleName("nn::hac::BucketTree"),
	mEntryCount(0),
	mNodeSize(0),
	mEntrySize(0)
{}

void nn::hac::BucketTree::parse(const std::shared_ptr<tc::io::IStream>& table_stream, size_t node_size, size_t entry_size, size_t entry_count)
{
	if (table_stream == nullptr)
	{
		throw tc::ArgumentNullException(mModuleName, "table_stream was null.");
	}
	if (!table_stream->canRead() || !table_stream->canSeek())
	{
		throw tc::InvalidOperationException(mModuleName, "table_stream did not support reading and or seeking.");
	}
	if (entry_size < sizeof(int64_t))
	{
		throw tc::ArgumentOutOfRangeException(mModuleName, "entry_size cannot be smaller than 8 bytes.");
	}
	if (node_size < entry_size + sizeof(sNodeHeader))
	{
		throw tc::ArgumentOutOfRangeException(mModuleName, "node_size was too small to store entry data.");
	}
	if (kNodeSizeMin > node_size || node_size > kNodeSizeMax)
	{
		throw tc::ArgumentOutOfRangeException(mModuleName, "node_size was outside valid node size range.");
	}
	if (!isPowerOfTwo(node_size))
	{
		throw tc::ArgumentOutOfRangeException(mModuleName, "node_size was not a power of two.");
	}
	if (entry_count == 0)
	{
		throw tc::ArgumentOutOfRangeException(mModuleName, "entry_count was zero.");
	}

	int64_t stream_length = table_stream->length();

	size_t expected_table_size = getHeaderNodeDataSize(node_size, entry_size, entry_count) + geEntryNodeDataSize(node_size, entry_size, entry_count);

	if (!tc::is_size_t_too_large_for_int64_t(expected_table_size) || stream_length < int64_t(expected_table_size))
	{
		throw tc::ArgumentException(mModuleName, "table_stream was too small.");
	}

	tc::ByteData bucket_tree_data = tc::ByteData(expected_table_size);
	
	// seek to begin
	table_stream->seek(0, tc::io::SeekOrigin::Begin);

	// read bucket_tree_data
	if (table_stream->read(bucket_tree_data.data(), bucket_tree_data.size()) != bucket_tree_data.size())
	{
		throw tc::io::IOException(mModuleName, "Failed to read raw bucket tree data.");
	}
}