#pragma once
#include "Mesh.h"
namespace RA_FRAMEWORK
{
	class GeometryGenerator
	{
	public:
		GeometryGenerator() = delete;
		GeometryGenerator(const GeometryGenerator&) = delete;
		GeometryGenerator& operator=(const GeometryGenerator&) = delete;
		~GeometryGenerator();
	public:
		static Mesh* GenerateQuad(float width, float height, bool negativeNormals = false, float z = 0.0f);
		static Mesh* GenerateSphere(const float radius, const uint rings, const uint sectors);
		static Mesh* GenerateCubeMap();
	};
}