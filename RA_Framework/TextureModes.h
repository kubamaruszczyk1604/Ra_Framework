#pragma once
#include "RAUtils.h"
namespace RA_FRAMEWORK
{
	enum class TextureType
	{
		D3D11TEXTURE = 0,
		GLTEXTURE = 1
	};

	enum class TextureAddressMode
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

	enum class TextureFormat
	{
		UBYTE = 0,
		BYTE = 1,
		USHORT = 2,
		SHORT = 3,
		UINT = 4,
		INT = 5,
		FLOAT = 6	    
	};
}