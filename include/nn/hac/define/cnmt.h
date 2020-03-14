#pragma once
#include <fnd/types.h>
#include <fnd/sha.h>

namespace nn
{
namespace hac
{
	namespace cnmt
	{
		enum class ContentType
		{
			Meta = 0,
			Program,
			Data,
			Control,
			HtmlDocument,
			LegalInformation,
			DeltaFragment
		};

		enum class ContentMetaType
		{
			SystemProgram = 1,
			SystemData,
			SystemUpdate,
			BootImagePackage,
			BootImagePackageSafe,

			Application = 0x80,
			Patch, // can have extended data
			AddOnContent,
			Delta // can have extended data
		};

		enum class UpdateType
		{
			ApplyAsDelta,
			Overwrite,
			Create
		};

		enum class ContentMetaAttribute
		{
			IncludesExFatDriver,
			Rebootless
		};

		static const size_t kContentIdLen = 0x10;
		static const size_t kDigestLen = 0x20;

		struct sContentId
		{
			byte_t data[kContentIdLen];

			void set(const byte_t content_id[kContentIdLen])
			{
				memcpy(this->data, content_id, kContentIdLen);
			}

			void operator=(const sContentId& other)
			{
				set(other.data);
			}

			bool operator==(const sContentId& other) const
			{
				return memcmp(this->data, other.data, kContentIdLen) == 0;
			}

			bool operator!=(const sContentId& other) const
			{
				return !(*this == other);
			}
		};

		struct sDigest
		{
			byte_t data[kDigestLen];

			void set(const byte_t digest[kDigestLen])
			{
				memcpy(this->data, digest, kDigestLen);
			}

			void operator=(const sDigest& other)
			{
				set(other.data);
			}

			bool operator==(const sDigest& other) const
			{
				return memcmp(this->data, other.data, kDigestLen) == 0;
			}

			bool operator!=(const sDigest& other) const
			{
				return !(*this == other);
			}
		};
	}


#pragma pack(push,1)
	/*
	struct sContentMeta
	{
		sContentMetaHeader hdr;
		byte_t exhdr[]; // optional
		sContentInfo info[];
		sContentMetaInfo meta[];
		byte_t extdata[];
		byte_t digest[32]
	};
	*/

	struct sContentMetaHeader
	{
		le_uint64_t id;
		le_uint32_t version;
		byte_t type;
		byte_t reserved_0;
		le_uint16_t exhdr_size;
		le_uint16_t content_count;
		le_uint16_t content_meta_count;
		byte_t attributes;
		byte_t reserved_1[3];
		le_uint32_t required_download_system_version;
		byte_t reserved_2[4];
	};
	static_assert(sizeof(sContentMetaHeader) == 0x20, "sContentMetaHeader size.");

	struct sContentInfo
	{
		fnd::sha::sSha256Hash content_hash;
		cnmt::sContentId content_id;
		le_uint32_t size_lower;
		le_uint16_t size_higher;
		byte_t content_type;
		byte_t id_offset;
	};
	static_assert(sizeof(sContentInfo) == 0x38, "sContentInfo size.");

	struct sContentMetaInfo
	{
		le_uint64_t id;
		le_uint32_t version;
		byte_t type;
		byte_t attributes;
		byte_t reserved[2];
	};
	static_assert(sizeof(sContentMetaInfo) == 0x10, "sContentMetaInfo size.");

	struct sApplicationMetaExtendedHeader
	{
		le_uint64_t patch_id;
		le_uint32_t required_system_version;
		le_uint32_t required_application_version;
	};
	static_assert(sizeof(sApplicationMetaExtendedHeader) == 0x10, "sApplicationMetaExtendedHeader size.");

	struct sPatchMetaExtendedHeader
	{
		le_uint64_t application_id;
		le_uint32_t required_system_version;
		le_uint32_t extended_data_size;
		byte_t reserved[8];
	};
	static_assert(sizeof(sPatchMetaExtendedHeader) == 0x18, "sPatchMetaExtendedHeader size.");

	struct sAddOnContentMetaExtendedHeader
	{
		le_uint64_t application_id;
		le_uint32_t required_application_version;
		byte_t reserved[4];
	};
	static_assert(sizeof(sAddOnContentMetaExtendedHeader) == 0x10, "sAddOnContentMetaExtendedHeader size.");

	struct sDeltaMetaExtendedHeader
	{
		le_uint64_t application_id;
		le_uint32_t extended_data_size;
		byte_t reserved[4];
	};
	static_assert(sizeof(sDeltaMetaExtendedHeader) == 0x10, "sDeltaMetaExtendedHeader size.");

	struct sSystemUpdateMetaExtendedHeader
	{
		le_uint32_t extended_data_size;
	};
	static_assert(sizeof(sSystemUpdateMetaExtendedHeader) == 0x4, "sSystemUpdateMetaExtendedHeader size.");

	/*
	struct sSystemUpdateMetaData
	{
		sSystemUpdateMetaExtendedDataHeader header;
		if (header.version == 1)
		{
			sFirmwareVariationInfo_v1 variation_info[header.variation_count];
		}
		else if (header.version == 2)
		{
			le_uint32_t firmware_variation_id[header.variation_count];
			sFirmwareVariationInfo_v2 variation_info[header.variation_count];
			sContentMetaInfo content_meta_info[total of variation_infos.meta_count IF refer_to_base is false]
		}
		else
		{
			undefined
		}
	}
	*/

	struct sSystemUpdateMetaExtendedDataHeader
	{
		le_uint32_t version;
		le_uint32_t variation_count;
	};
	static_assert(sizeof(sSystemUpdateMetaExtendedDataHeader) == 0x8, "sSystemUpdateMetaExtendedDataHeader size.");

	struct sFirmwareVariationInfo_v1
	{
		le_uint32_t firmware_variation_id;
		byte_t reserved_x04[0x1C];
	};
	static_assert(sizeof(sFirmwareVariationInfo_v1) == 0x20, "sFirmwareVariationInfo_v1 size.");

	struct sFirmwareVariationInfo_v2
	{
		byte_t refer_to_base;
		byte_t reserved_x01[3];
		le_uint32_t meta_count;
		byte_t reserved_x08[24];
	};
	static_assert(sizeof(sFirmwareVariationInfo_v2) == 0x20, "sFirmwareVariationInfo_v2 size.");

#pragma pack(pop)
}
}