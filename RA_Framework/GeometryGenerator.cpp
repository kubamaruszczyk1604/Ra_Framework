#include "GeometryGenerator.h"
namespace RA_FRAMEWORK
{
	GeometryGenerator::~GeometryGenerator(){}

	Mesh* GeometryGenerator::GenerateQuad(float width, float height, bool negativeNormals, float z)
	{
		Mesh* mesh = new Mesh();
		width *= 0.5; height *= 0.5f;
		float fbDist = z;
		float normZ = 1.0f - (2.0f*static_cast<float>(negativeNormals));
		//front culling
		mesh->AddVertex(Vertex(-width, -height, fbDist, 0, 0, normZ, 0, 0));
		mesh->AddVertex(Vertex(width, -height, fbDist, 0, 0, normZ, 1, 0));
		mesh->AddVertex(Vertex(width, height, fbDist, 0, 0, normZ, 1, 1));
		mesh->AddVertex(Vertex(-width, height, fbDist, 0, 0, normZ, 0, 1));

		std::vector<unsigned> indices{ 0, 1, 2, 0, 2, 3 };
		mesh->CreateVertexBuffer(indices);
		return mesh;
	}

	Mesh * GeometryGenerator::GenerateSphere(const float radius, const uint rings, const uint sectors)
	{
		float const R = 1.0f / (float)(rings - 1);
		float const S = 1.0f / (float)(sectors - 1);
		const float PI = 3.141592654f;
		const float Half_PI = PI * 0.5f;
		Mesh* meshOut = new Mesh();
		for (uint r = 0; r < rings; r++)
		{
			for (uint s = 0; s < sectors; s++)
			{
				float const y = sin(-Half_PI + PI * r * R);
				float const x = cos(2 * PI * s * S) * sin(PI * r * R);
				float const z = sin(2 * PI * s * S) * sin(PI * r * R);
				Vec2 UV(s * S, r * R); Vec3 Norm(x, y, z);
				Vec3 Pos(x * radius, y * radius, z * radius);
				meshOut->AddVertex(Vertex(Pos.x, Pos.y, Pos.z, Norm.x, Norm.y, Norm.z, UV.x, UV.y));
			}
		}
		std::vector<unsigned> sphere_indices;
		for (uint r = 0; r < rings; r++)
		{
			for (uint s = 0; s < sectors; s++)
			{
				sphere_indices.push_back((r + 1) * sectors + (s + 1));
				sphere_indices.push_back(r * sectors + (s + 1));
				sphere_indices.push_back(r * sectors + s);
				sphere_indices.push_back((r + 1) * sectors + s);
				sphere_indices.push_back((r + 1) * sectors + (s + 1));
				sphere_indices.push_back((r * sectors + s));
			}
		}
		meshOut->CreateVertexBuffer(sphere_indices);
		return meshOut;
	}
}