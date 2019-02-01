#pragma once
#include "ShaderProgram.h"
#include "GLShader.h"
namespace RA_FRAMEWORK
{
	class GLShaderProgram: public ShaderProgram
	{

	private:
		GLuint m_ProgId;
		GLShader* p_VertexShader;
		GLShader* p_FragmentShader;
		bool m_Created{ false };


	public:
		GLShaderProgram(GLShader* vertexShader, GLShader* fragmentShader);
		virtual ~GLShaderProgram();

		GLShaderProgram& operator=(GLShaderProgram&) = delete;
		GLShaderProgram(const GLShaderProgram&) = delete;

		bool Create() override;
		bool SetAsCurrent() override;
		GLuint GetID() { return m_ProgId; }
	};

}
