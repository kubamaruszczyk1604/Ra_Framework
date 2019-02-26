#pragma once
#include "VBO.h"
#include "RAUtils.h"
#include <array>
namespace RA_FRAMEWORK
{
	class GLVBO : public VBO
	{
	private:
		static const std::array<int, 5> LookupTableTopologyType;
		GLuint ptr_VBO[2];
		GLuint ptr_VAO;
		int m_VertexCount;
		int m_IndexCount;
		int* m_indicesPtr;
		std::vector<unsigned> m_Indices;
	public:
		GLVBO();
		GLVBO(const GLVBO&) = delete;
		GLVBO& operator=(const GLVBO&) = delete;
		~GLVBO();
	public:
		bool							Create(Vertex* vertices, const int numVertices);
		void							Draw(PrimitiveType primitiveType) const;
		bool							CreateIndexBuffer(unsigned * const indices, const unsigned numInidices);
		const std::vector<unsigned>&	GetIndices()const { return m_Indices; };
	};
}
