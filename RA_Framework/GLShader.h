#pragma once
#include "Shader.h"
#include "RAUtils.h"
namespace RA_FRAMEWORK
{
	class GLShader : public Shader
	{
	private:
		GLuint m_Id;
	public:
		GLShader(ShaderType type);
		GLShader(const GLShader&) = delete;
		GLShader& operator=(const GLShader&) = delete;
		virtual ~GLShader();
	public:
		bool LoadFromFile(const std::string& path);
		void SetShaderString(const std::string& content);
		bool Compile(std::string& log);
		GLuint GetID();
	};
}