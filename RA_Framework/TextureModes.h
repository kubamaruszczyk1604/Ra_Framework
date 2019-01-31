#pragma once
#include "RAUtils.h"
#include "GLTexture.h"
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
		NEAREST = GL_NEAREST,
		BILINEAR = GL_LINEAR,
		NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
		BILINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
		BILINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
	};


	enum class TextureFormat
	{
		UBYTE = GL_UNSIGNED_BYTE,
		BYTE = GL_BYTE,
		USHORT = GL_UNSIGNED_SHORT,
		SHORT = GL_SHORT,
		UINT = GL_UNSIGNED_INT,
		INT = GL_INT,
		FLOAT = GL_FLOAT
	    
	};



}