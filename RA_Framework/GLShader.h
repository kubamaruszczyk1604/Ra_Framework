#pragma once
#include "Shader.h"
#include "RAUtils.h"

namespace RA_FRAMEWORK
{

	class GLShader : public Shader
	{
	public:
		GLShader(ShaderType type);
		virtual ~GLShader();

		GLShader(const GLShader&) = delete;
		GLShader& operator=(const GLShader&) = delete;


		bool LoadFromFile(const std::string& path);
		void SetShaderString(const std::string& content);
		bool Compile(std::string& log);
		GLuint GetID();

	private:
		GLuint m_Id;

	};


}
