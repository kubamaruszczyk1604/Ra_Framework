#ifndef _RA_TYPES_H
#define _RA_TYPES_H
#include <exception>
#include <string>
#include <iostream>

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
	using Vec2 = glm::vec2;
	using Vec3 = glm::vec3;
	using Vec4 = glm::vec4;
	using Colour = glm::vec4;
	using Mat4 = glm::mat4;
	using Quat = glm::quat;

#define PRINT(P) std::cout<<P<<std::endl;

	//Example PREDICATE(int,Object==2)
#define UNARY_PRED1(T,condition) [](T const& Object) { return condition; }
#define UNARY_PRED2(T,condition) [](T const& ObjectA,T const& ObjectB) { return condition; }

}

#endif