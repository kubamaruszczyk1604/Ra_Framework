#pragma once
#include "GLVBO.h"
namespace RA_FRAMEWORK
{
	class Mesh
	{
	private:
		std::vector<Vertex> m_Vertices;
		VBO* m_pVBO;
		bool m_BuffersCreated;
	public:
		Mesh();
		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;
		~Mesh();
	public:
		bool			AddVertex(const Vertex& v);
		const VBO*		CreateVertexBuffer();
		const VBO*		CreateVertexBuffer(std::vector<unsigned>& indices);
	public:
		VBO*			GetVBO() { return m_pVBO; }
	};
}