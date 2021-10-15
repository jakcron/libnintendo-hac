#include <nn/hac/HierarchicalValidatedStream.h>
#include <tc/io/SubStream.h>
#include <tc/io/IOUtil.h>
#include <tc/io/StreamUtil.h>

#include <tc/cli/FormatUtil.h>
#include <fmt/format.h>

nn::hac::HierarchicalValidatedStream::HierarchicalValidatedStream() :
	mModuleLabel("nn::hac::HierarchicalValidatedStream"),
	mBaseStream(),
	mDataStreamBlockSize(0),
	mDataStreamLogicalLength(0),
	mDataStream(),
	mHashCache(),
	mHashCalc(new tc::crypto::Sha256Generator())
{
}

nn::hac::HierarchicalValidatedStream::HierarchicalValidatedStream(const std::shared_ptr<tc::io::IStream>& stream, const StreamInfo& info) :
	HierarchicalValidatedStream()
{
	mBaseStream = stream;

	// validate stream properties
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException("nn::hac::HierarchicalValidatedStream", "stream is null.");
	}
	if (mBaseStream->canRead() == false)
	{
		throw tc::InvalidOperationException("nn::hac::HierarchicalValidatedStream", "stream does not support reading.");
	}
	if (mBaseStream->canSeek() == false)
	{
		throw tc::InvalidOperationException("nn::hac::HierarchicalValidatedStream", "stream does not support seeking.");
	}

	// process hash layers sections
	struct InternalHashLayerInfo
	{
		tc::ByteData hash_data;
		size_t block_size;
		size_t block_num;
	};

	std::vector<InternalHashLayerInfo> hash_layer_info;

	for (size_t i = 0; i < info.hash_layer_info.size(); i++)
	{
		if (tc::is_int64_t_too_large_for_size_t(info.hash_layer_info[i].size))
		{
			throw tc::Exception(mModuleLabel, fmt::format("HashLayer[{:d}].size was too large to read into memory.", i));
		}
		if (tc::is_int64_t_too_large_for_size_t(info.hash_layer_info[i].block_size) || (info.hash_layer_info[i].block_size & (info.hash_layer_info[i].block_size - 1)) != 0)
		{
			throw tc::Exception(mModuleLabel, fmt::format("HashLayer[{:d}].block_size was invalid.", i));
		}
		
		InternalHashLayerInfo layer_info;

		layer_info.hash_data = tc::ByteData(tc::io::IOUtil::castInt64ToSize(info.hash_layer_info[i].size));
		layer_info.block_size = tc::io::IOUtil::castInt64ToSize(info.hash_layer_info[i].block_size);
		layer_info.block_num = layer_info.hash_data.size() / layer_info.block_size + ((layer_info.hash_data.size() % layer_info.block_size) != 0 ? 1 : 0);

		mBaseStream->seek(info.hash_layer_info[i].offset, tc::io::SeekOrigin::Begin);
		mBaseStream->read(layer_info.hash_data.data(), layer_info.hash_data.size());

		hash_layer_info.push_back(std::move(layer_info));
	}

	// validate hash layers
	for (size_t i = 0; i < hash_layer_info.size(); i++)
	{
		if (validateLayerBlocksWithHashLayer(hash_layer_info[i].hash_data.data(), hash_layer_info[i].hash_data.size(), hash_layer_info[i].block_size, hash_layer_info[i].block_num, info.align_hash_layer_to_block, (i == 0 ? info.master_hash_data.data() : hash_layer_info[i - 1].hash_data.data())))
		{
			throw tc::crypto::CryptoException(mModuleLabel, fmt::format("HashLayer[{:d}] failed hash verification.", i));
		}
	}

	// process data layer
	if (tc::is_int64_t_too_large_for_size_t(info.data_layer_info.block_size) || (info.data_layer_info.block_size & (info.data_layer_info.block_size - 1)) != 0)
	{
		throw tc::Exception(mModuleLabel, "DataLayer.block_size was invalid.");
	}

	// save hash data for data layer
	mHashCache = hash_layer_info.back().hash_data;

	// create data layer
	mDataStreamBlockSize = tc::io::IOUtil::castInt64ToSize(info.data_layer_info.block_size);
	mDataStreamLogicalLength = info.data_layer_info.size;
	size_t data_block_num = tc::io::IOUtil::castInt64ToSize(info.data_layer_info.size / info.data_layer_info.block_size) + ((info.data_layer_info.size % info.data_layer_info.block_size != 0) ? 1 : 0);
	mDataStream = std::shared_ptr<tc::io::SubStream>(new tc::io::SubStream(mBaseStream, info.data_layer_info.offset, tc::io::IOUtil::castSizeToInt64(data_block_num) * tc::io::IOUtil::castSizeToInt64(mDataStreamBlockSize)));
}

bool nn::hac::HierarchicalValidatedStream::canRead() const
{
	return mDataStream == nullptr ? false : mDataStream->canRead();
}

bool nn::hac::HierarchicalValidatedStream::canWrite() const
{
	return false; // always false this is a read-only stream
}
bool nn::hac::HierarchicalValidatedStream::canSeek() const
{
	return mDataStream == nullptr ? false : mDataStream->canSeek();
}

int64_t nn::hac::HierarchicalValidatedStream::length()
{
	return mDataStream == nullptr ? 0 : mDataStreamLogicalLength;
}

int64_t nn::hac::HierarchicalValidatedStream::position()
{
	return mDataStream == nullptr ? 0 : mDataStream->position();
}

size_t nn::hac::HierarchicalValidatedStream::read(byte_t* ptr, size_t count)
{
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::read()", "Failed to read from stream (stream is disposed)");
	}
	
	// track read_count
	size_t data_read_count = 0;

	// get predicted read count
	count = tc::io::IOUtil::getReadableCount(this->length(), this->position(), count);
	
	// if count is 0 just return
	if (count == 0) return data_read_count;

	// determine begin & end offsets
	int64_t begin_read_offset = this->position();
	int64_t end_read_offset   = begin_read_offset + tc::io::IOUtil::castSizeToInt64(count);
	int64_t begin_aligned_offset = begin_read_offset - offsetInBlock(begin_read_offset);
	int64_t end_aligned_offset   = end_read_offset - offsetInBlock(end_read_offset) + (offsetInBlock(end_read_offset) ? mDataStreamBlockSize : 0x0);
	size_t block_num = offsetToBlock(end_aligned_offset - begin_aligned_offset);

	bool read_partial_begin_block     = false;
	size_t partial_begin_block        = offsetToBlock(begin_read_offset);
	size_t partial_begin_block_offset = 0;
	size_t partial_begin_block_size   = mDataStreamBlockSize;

	bool read_partial_end_block     = false;
	size_t partial_end_block        = offsetToBlock(end_read_offset);
	size_t partial_end_block_offset = 0;
	size_t partial_end_block_size   = mDataStreamBlockSize;

	if (offsetInBlock(begin_read_offset) != 0)
	{
		read_partial_begin_block   = true;
		partial_begin_block_offset += offsetInBlock(begin_read_offset);
		partial_begin_block_size   -= partial_begin_block_offset;
	}
	if (offsetInBlock(end_read_offset) != 0)
	{
		if (partial_begin_block == partial_end_block)
		{
			read_partial_begin_block = true;
			partial_begin_block_size -= (mDataStreamBlockSize - offsetInBlock(end_read_offset));
		}
		else
		{
			read_partial_end_block = true;
			partial_end_block_size = offsetInBlock(end_read_offset);
		}
	}

	size_t continuous_block_num   = block_num - (size_t)read_partial_begin_block - (size_t)read_partial_end_block;
	size_t continuous_begin_block = (continuous_block_num == 0) ? 0 : (offsetToBlock(begin_aligned_offset) + (size_t)read_partial_begin_block);

	/*
	std::cout << "##############################################" << std::endl;
	std::cout << "count:                  0x" << std::hex << count << std::endl;
	std::cout << "begin_read_offset:      0x" << std::hex << begin_read_offset << std::endl;
	std::cout << "end_read_offset:        0x" << std::hex << end_read_offset << std::endl;
	std::cout << "begin_aligned_offset:   0x" << std::hex << begin_aligned_offset << std::endl;
	std::cout << "end_aligned_offset:     0x" << std::hex << end_aligned_offset << std::endl;
	std::cout << "block_num:              0x" << std::hex << block_num << std::endl;
	
	std::cout << "partial_begin:" << std::endl;
	std::cout << "  read_block:           " << std::boolalpha << read_partial_begin_block << std::endl;
	std::cout << "  block:                0x" << std::hex << partial_begin_block << std::endl;
	std::cout << "  offset:               0x" << std::hex << partial_begin_block_offset << std::endl;
	std::cout << "  size:                 0x" << std::hex << partial_begin_block_size << std::endl;

	std::cout << "partial_end:" << std::endl;
	std::cout << "  read_block:           " << std::boolalpha << read_partial_end_block << std::endl;
	std::cout << "  block:                0x" << std::hex << partial_end_block << std::endl;
	std::cout << "  offset:               0x" << std::hex << partial_end_block_offset << std::endl;
	std::cout << "  size:                 0x" << std::hex << partial_end_block_size << std::endl;

	std::cout << "continuous:" << std::endl;
	std::cout << "  block:                0x" << std::hex << continuous_begin_block << std::endl;
	std::cout << "  block_num:            0x" << std::hex << continuous_block_num << std::endl;
	*/

	if (block_num == 0)
	{
		tc::InvalidOperationException("nn::hac::HierarchicalValidatedStream", "Invalid block number (0 blocks, would have returned before now if count==0)");
	}

	if (block_num < continuous_block_num)
	{
		tc::InvalidOperationException("nn::hac::HierarchicalValidatedStream", "Invalid block number (underflow error)");
	}

	// allocate memory for partial block
	tc::ByteData partial_block = tc::ByteData(mDataStreamBlockSize);

	// read un-aligned begin block
	if (read_partial_begin_block)
	{	
		// read block
		this->seek(blockToOffset(partial_begin_block), tc::io::SeekOrigin::Begin);
		mDataStream->read(partial_block.data(), partial_block.size());
		
		// verify block
		if (validateLayerBlocksWithHashLayer(partial_block.data(), mDataStreamBlockSize, 1, getBlockHash(partial_begin_block)) == false)
		{
			throw tc::crypto::CryptoException("nn::hac::HierarchicalValidatedStream", "Data layer block(s) failed hash validation.");
		}

		// copy out block carving
		memcpy(ptr + data_read_count, partial_block.data() + partial_begin_block_offset, partial_begin_block_size);

		// increment data read count
		data_read_count += partial_begin_block_size;
	}

	// read continous blocks
	if (continuous_block_num > 0)
	{
		// read blocks
		this->seek(blockToOffset(continuous_begin_block), tc::io::SeekOrigin::Begin);
		mDataStream->read(ptr + data_read_count, continuous_block_num * mDataStreamBlockSize);
		
		// verify blocks
		if (validateLayerBlocksWithHashLayer(ptr + data_read_count, mDataStreamBlockSize, continuous_block_num, getBlockHash(continuous_begin_block)) == false)
		{
			throw tc::crypto::CryptoException("nn::hac::HierarchicalValidatedStream", "Data layer block(s) failed hash validation.");
		}

		// increment data read count
		data_read_count += continuous_block_num * mDataStreamBlockSize;
	}
	
	// read un-aligned end block
	if (read_partial_end_block)
	{
		// read block
		this->seek(blockToOffset(partial_end_block), tc::io::SeekOrigin::Begin);
		mDataStream->read(partial_block.data(), partial_block.size());
		
		// verify block
		if (validateLayerBlocksWithHashLayer(partial_block.data(), mDataStreamBlockSize, 1, getBlockHash(partial_end_block)) == false)
		{
			throw tc::crypto::CryptoException("nn::hac::HierarchicalValidatedStream", "Data layer block(s) failed hash validation.");
		}

		// copy out block carving
		memcpy(ptr + data_read_count, partial_block.data() + partial_end_block_offset, partial_end_block_size);

		// increment
		data_read_count += partial_end_block_size;
	}

	// restore expected logical position
	this->seek(begin_read_offset + tc::io::IOUtil::castSizeToInt64(data_read_count), tc::io::SeekOrigin::Begin);

	// return data read count
	return data_read_count;
}

size_t nn::hac::HierarchicalValidatedStream::write(const byte_t* ptr, size_t count)
{
	throw tc::NotImplementedException(mModuleLabel+"::write()", "write is not supported for HierarchicalValidatedStream");
}

int64_t nn::hac::HierarchicalValidatedStream::seek(int64_t offset, tc::io::SeekOrigin origin)
{
	if (mDataStream == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::seek()", "Failed to set stream position (stream is disposed)");
	}
	
	return mDataStream->seek(offset, origin);
}

void nn::hac::HierarchicalValidatedStream::setLength(int64_t length)
{
	if (mDataStream == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::setLength()", "Failed to set stream length (stream is disposed)");
	}

	throw tc::NotSupportedException(mModuleLabel+"::setLength()", "setLength is not supported for HierarchicalValidatedStream");
}

void nn::hac::HierarchicalValidatedStream::flush()
{
	if (mDataStream == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::seek()", "Failed to flush stream (stream is disposed)");
	}

	mDataStream->flush();
	mBaseStream->flush();
}

void nn::hac::HierarchicalValidatedStream::dispose()
{
	if (mDataStream.get() != nullptr)
	{
		// dispose data stream
		mDataStream->dispose();

		// release ptr
		mDataStream.reset();
	}

	if (mBaseStream.get() != nullptr)
	{
		// dispose base stream
		mBaseStream->dispose();

		// release ptr
		mBaseStream.reset();
	}
	
	// clear hash cache
	mHashCache = tc::ByteData();
}

bool nn::hac::HierarchicalValidatedStream::validateLayerBlocksWithHashLayer(const byte_t* layer, size_t block_size, size_t block_num, const byte_t* hash_layer)
{
	size_t bad_block = block_num;
	for (size_t i = 0; i < block_num; i++)
	{
		const byte_t* blk_ptr = layer + (block_size * i);
		size_t blk_size = block_size;

		const byte_t* blk_hash_ptr = hash_layer + (mHashCalc->kHashSize * i);
		//std::cout << tc::cli::FormatUtil::formatBytesAsHxdHexString(blk_hash_ptr, block_size);

		mHashCalc->initialize();
		mHashCalc->update(blk_ptr, blk_size);
		mHashCalc->getHash(mHash.data());

		//std::cout << "test hash: " << tc::cli::FormatUtil::formatBytesAsString(blk_hash_ptr, 32, true, ":") << std::endl;
		//std::cout << "calc hash: " << tc::cli::FormatUtil::formatBytesAsString(mHash.data(), 32, true, ":") << std::endl;

		// if good hash, reduce bad block count
		if (memcmp(mHash.data(), blk_hash_ptr, mHashCalc->kHashSize) == 0)
		{
			bad_block -= 1;
		}
		else
		{
			//std::cout << "BadBlock:" << std::endl;
			//std::cout << tc::cli::FormatUtil::formatBytesAsHxdHexString(blk_ptr, block_size);
		}
		
	}

	return bad_block == 0;
}

bool nn::hac::HierarchicalValidatedStream::validateLayerBlocksWithHashLayer(const byte_t* layer, size_t layer_size, size_t block_size, size_t block_num, bool align_partial_block_to_blocksize, const byte_t* hash_layer)
{
	size_t partial_final_block_size = layer_size % block_size;

	size_t bad_block = block_num;
	for (size_t i = 0; i < block_num; i++)
	{
		const byte_t* blk_ptr = layer + (block_size * i);
		size_t blk_size = (i+1 == block_num && partial_final_block_size != 0 && !align_partial_block_to_blocksize) ? partial_final_block_size : block_size;

		const byte_t* blk_hash_ptr = hash_layer + (mHashCalc->kHashSize * i);
		//std::cout << tc::cli::FormatUtil::formatBytesAsHxdHexString(blk_hash_ptr, block_size);

		mHashCalc->initialize();
		mHashCalc->update(blk_ptr, blk_size);
		mHashCalc->getHash(mHash.data());

		//std::cout << "test hash: " << tc::cli::FormatUtil::formatBytesAsString(blk_hash_ptr, 32, true, ":") << std::endl;
		//std::cout << "calc hash: " << tc::cli::FormatUtil::formatBytesAsString(mHash.data(), 32, true, ":") << std::endl;

		// if good hash, reduce bad block count
		if (memcmp(mHash.data(), blk_hash_ptr, mHashCalc->kHashSize) == 0)
		{
			bad_block -= 1;
		}
		else
		{
			//std::cout << "BadBlock:" << std::endl;
			//std::cout << tc::cli::FormatUtil::formatBytesAsHxdHexString(blk_ptr, block_size);
		}

	}

	return bad_block == 0;
}