#pragma once
#include "RAUtils.h"
namespace RA_FRAMEWORK
{
	enum class TextureWrapMode
	{
		WRAP = 0,
		MIRROR = 1,
		CLAMP = 2,
		BORDER = 3,
		MIRROR_ONCE = 4
	};

	enum class TextureFilterMode
	{
		NEAREST = 0,
		BILINEAR = 1,
		NEAREST_MIPMAP_NEAREST = 2,
		BILINEAR_MIPMAP_NEAREST = 3,
		BILINEAR_MIPMAP_LINEAR = 4
	};

	enum class InputPixelDataType
	{
		UNISGNED_BYTE = 0,
		BYTE = 1,
		UNSIGNED_SHORT = 2,
		SHORT = 3,
		UNSIGNED_INT = 4,
		INT = 5,
		FLOAT = 6,
		DOUBLE = 7
	};

	enum class InputPixelFormat
	{
		RGB = 0,
	    RGBA = 1,
		BGR = 2,
		BGRA = 3,
		DEPTH_COMPONENT = 4,
		DEPTH_STENCIL = 5
	};

	enum class TextureDataFormat
	{
		RGB = 0,
		RGBA = 1,
		BGR = 2,
		BGRA = 3,
		DEPTH_COMPONENT = 4,
		DEPTH_STENCIL = 5,
		RGB4 = 6,
		RGB5 = 7,
		RGB8 = 8,
		RGB8_SIGNED_NORMALIZED = 9,
		RGB10 = 10,
		RGB12 = 11,
		RGB16_SIGNED_NORMALIZED = 12,
		RGBA2 = 13,
		RGBA4 = 14,
		RGBA8 = 15,
		RGBA8_SIGNED_NORMALIZED = 16,
		RGBA12 = 17,
		RGBA16 = 18,
		SRGB8 = 19,
		SRGB8_ALPHA = 20,
		RGB16F = 21,
		RGB32F = 22,
		RGBA16F = 23,
		RGBA32F = 24
	};
}