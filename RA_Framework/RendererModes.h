#pragma once
namespace RA_FRAMEWORK
{
	enum class CullMode
	{
		BACK = 0,
		FRONT = 1,
		FRONT_AND_BACK = 2,
		NONE = 3
	};
	enum class FillMode
	{
		SOLID = 0,
		WIREFRAME = 1
	};
	enum class DepthQualifier
	{
		LESS = 0,
	    EQUAL = 1,
		LESS_AND_EQUAL = 2,
		GREATER = 3,
		GREATER_AND_EQUAL = 4,
		ALWAYS_PASS = 5,
		NEVER_PASS = 6
	};

//#define GL_LESS 0x0201
//#define GL_EQUAL 0x0202
//#define GL_LEQUAL 0x0203
//#define GL_GREATER 0x0204
//#define GL_NOTEQUAL 0x0205
//#define GL_GEQUAL 0x0206
//#define GL_ALWAYS 0x0207
}