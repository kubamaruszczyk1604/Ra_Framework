#pragma once
namespace RA_FRAMEWORK
{
	enum class CullMode
	{
		BACK				= 0,
		FRONT				= 1,
		FRONT_AND_BACK		= 2,
		NONE				= 3
	};
	enum class FillMode
	{
		SOLID				= 0,
		WIREFRAME			= 1
	};
	enum class DepthQualifier
	{
		LESS				= 0,
	    EQUAL				= 1,
		LESS_AND_EQUAL		= 2,
		GREATER				= 3,
		GREATER_AND_EQUAL	= 4,
		ALWAYS_PASS			= 5,
		NEVER_PASS			= 6
	};
}