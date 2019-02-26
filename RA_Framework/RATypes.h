#ifndef _RA_TYPES_H
#define _RA_TYPES_H
#include <exception>
#include <string>
#include <iostream>
#include <vector>

#include "GLM\GLM.hpp"
#include "GLM\GTC\matrix_transform.hpp"
#include "GLM\GTC\type_ptr.hpp"
#include <GLM\GTC\matrix_transform.hpp>

namespace RA_FRAMEWORK
{
	using RAbyte = char;
	using Exception = std::exception;
	using String = std::string;

	using RAint8 = signed char;
	using RAint16 = signed short;
	using RAint32 = signed int;
	using RAint64 = signed __int64;
	using RAuint8 = unsigned char;
	using RAuint16 = unsigned short;
	using RAuint32 = unsigned int;
	using RAuint64 = unsigned __int64;

	using RAfloat = float;

	using Vec2i = glm::ivec2;
	using Vec3i = glm::ivec3;
	using Vec4i = glm::ivec4;
	using Vec2 = glm::vec2;
	using Vec3 = glm::vec3;
	using Vec4 = glm::vec4;
	using Colour = glm::vec4;
	using Mat2 = glm::mat2;
	using Mat3 = glm::mat3;
	using Mat4 = glm::mat4;
	using Quat = glm::quat;

	class Entity;
	using EntityUnique = std::unique_ptr<Entity>;
	using ListOfEntities = std::vector<EntityUnique>;
	using RENDER_MASK = unsigned;
	enum  RENDER_MASK_ELEMENT
	{
		RENDERABLE					= 1,
		LIGHT_RECEIVER				= 1 << 1,
		REFLECTION_RECEIVER			= 1 << 2,
		SHADOW_RECEIVER				= 1 << 3,
		REFLECTION_CASTER			= 1 << 4,
		SHADOW_CASTER				= 1 << 5,
		UI							= 1 << 6

	};
	enum class GfxAPI
	{
		D3D11 = 0,
		GL = 1
	};

#define PRINT(P) std::cout<<P<<std::endl;

	//Example PREDICATE(int,Object==2)
#define UNARY_PRED1(T,condition) [](T const& Object) { return condition; }
#define UNARY_PRED2(T,condition) [](T const& ObjectA,T const& ObjectB) { return condition; }

}

#endif