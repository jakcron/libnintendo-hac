#pragma once
#include <nn/hac/define/types.h>
#include <fnd/rsa.h>
#include <nn/hac/define/macro.h>

namespace nn
{
namespace hac
{
	namespace nrr
	{
		static const uint32_t kNrrStructMagic = _MAKE_STRUCT_MAGIC_U32("NRR0");

		enum class NrrKind : byte_t
		{
			User = 0,
			JitPlugin = 1
		};
	}

#pragma pack(push,1)
	struct sNrrCertificate
	{
		le_uint64_t application_id_mask;
		le_uint64_t application_id_pattern;
		byte_t reserved_00[0x10];
		byte_t nrr_body_modulus[fnd::rsa::kRsa2048Size];
		byte_t nrr_cert_signature[fnd::rsa::kRsa2048Size];
	};
	static_assert(sizeof(sNrrCertificate) == 0x220, "sNrrCertificate size.");

	struct sNrrHeader
	{
		le_uint32_t st_magic;
		byte_t certificate_key_generation;
		byte_t reserved_0[0xB];
		sNrrCertificate certificate;
		byte_t nrr_body_signature[fnd::rsa::kRsa2048Size];
	};
	static_assert(sizeof(sNrrHeader) == 0x330, "sNrrHeader size.");

	struct sNrrBodyHeader
	{
		le_uint64_t application_id;
		le_uint32_t size;
		byte_t nrr_kind;
		byte_t reserved_0[3];
		le_uint32_t hash_offset;
		le_uint32_t hash_count;
		byte_t reserved_1[8];
	};
	static_assert(sizeof(sNrrBodyHeader) == 0x20, "sNrrBodyHeader size.");

#pragma pack(pop)
}
}