#pragma once
#include <fnd/types.h>
#include <cstdint>
#include <cstring>
#include <bitset>

template <size_t N>
struct sFixedSizeArray
{
	uint8_t data[N];

	sFixedSizeArray()
	{
		memset(this->data, 0, N);
	}

	sFixedSizeArray(const uint8_t* data)
	{
		memcpy(this->data, data, N);
	}

	void set(const uint8_t* data)
	{
		memcpy(this->data, data, N);
	}

	uint8_t* get() const
	{
		return this->data;
	}

	size_t size() const
	{
		return N;
	}

	sFixedSizeArray<N>& operator=(const sFixedSizeArray<N>& other)
	{
		memcpy(this->data, other.data, N);

		return *this;
	}

	bool operator==(const sFixedSizeArray<N>& other) const
	{
		return memcmp(this->data, other.data, N) == 0;
	}

	bool operator!=(const sFixedSizeArray<N>& other) const
	{
		return !(*this == other);
	}
};