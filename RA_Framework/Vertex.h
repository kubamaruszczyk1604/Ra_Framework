#pragma once
#include "RAUtils.h"
namespace RA_FRAMEWORK
{
	struct Vertex
	{
		Vec3 Position;
		Vec3 Normal;
		Vec3 Tangent;
		Vec2 Texcoord0;

		Vertex(const float& x, const float& y, const float& z)
		{
			Position = Vec3(x, y, z);
		} 

		Vertex(const float& x, const float& y, const float& z, const float& u, const float& v)
		{
			Position = Vec3(x, y, z);
			Texcoord0.x = u;
			Texcoord0.y = v;
		}

		Vertex(const float& x, const float& y, const float& z, const float& nx, const float& ny, const float& nz, const float& u, const float& v)
		{
			Position = Vec3(x, y, z);
			Normal = Vec3(nx, ny, nz);
			Texcoord0.x = u;
			Texcoord0.y = v;
		}

		Vertex(const Vec3& pos)
		{
			Position = pos;
		}

		Vertex(const Vec3& pos, const Vec3& norm)
		{
			Position = pos;
			Normal = norm;
		}

		Vertex(const Vec3& pos, const Vec3& norm, const Vec2 texcoord)
		{
			Position = pos;
			Normal = norm;
			Texcoord0 = texcoord;
		}

		Vertex(const Vec3& pos, const Vec2 texcoord)
		{
			Position = pos;
			Texcoord0 = texcoord;
		}
	};
}