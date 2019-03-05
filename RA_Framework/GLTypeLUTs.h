#pragma once
#include "GL\glew.h"
namespace RA_FRAMEWORK
{
	static const unsigned DEPTH_QALIF_LUT_GL[7] = 
	{ GL_LESS, GL_EQUAL, GL_LEQUAL, GL_GREATER, GL_GEQUAL,GL_ALWAYS, GL_NEVER };

	static const unsigned TEX_FILTER_LUT_GL[5] =
	{ GL_NEAREST, GL_LINEAR, GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_LINEAR};

	static const unsigned TEX_ADDRESS_MODE_LUT_GL[5] =
	{ GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP, GL_CLAMP_TO_BORDER, GL_MIRROR_CLAMP_TO_EDGE };

	static const unsigned PIXEL_DATA_TYPE_LUT_GL[8] =
	{ GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT, GL_INT, GL_FLOAT, GL_DOUBLE };

	static const unsigned PIXEL_DATA_FORMAT_LUT_GL[6] =
	{ GL_RGB, GL_RGBA, GL_BGR, GL_BGRA, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL };

	static const unsigned TEX_INTERNAL_DATA_FORMAT_LUT_GL[25] =
	{
		GL_RGB, GL_RGBA, GL_BGR, GL_BGRA, GL_DEPTH_COMPONENT24, GL_DEPTH_STENCIL,
		GL_RGB4, GL_RGB5, GL_RGB8, GL_RGB8_SNORM, GL_RGB10, GL_RGB12,
		GL_RGB16_SNORM, GL_RGBA2, GL_RGBA4, GL_RGBA8,GL_RGBA8_SNORM, GL_RGBA12,
		GL_RGBA16, GL_SRGB8, GL_SRGB8_ALPHA8, GL_RGB16F, GL_RGB32F, GL_RGBA16F,
		GL_RGBA32F
	};
}