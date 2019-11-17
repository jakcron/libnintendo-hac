#include <nn/hac/GameCardUtils.h>

void nn::hac::GameCardUtils::getXciHeaderAesIv(const nn::hac::sGcHeader* hdr, byte_t* iv)
{
	for (size_t i = 0; i < 16; i++)
	{
		iv[15-i] = hdr->aescbc_iv.iv[i];
	}
}

void nn::hac::GameCardUtils::decryptXciHeader(nn::hac::sGcHeader* hdr, const byte_t* key)
{
	byte_t iv[fnd::aes::kAesBlockSize];

	getXciHeaderAesIv(hdr, iv);
	// decrypt encrypted data
	fnd::aes::AesCbcDecrypt(hdr->extended_header.raw_data, nn::hac::gc::kHeaderEncSize, key, iv, hdr->extended_header.raw_data);
}