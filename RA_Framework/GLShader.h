#pragma once
#include "Shader.h"
#include "RAUtils.h"
namespace RA_FRAMEWORK
{
	class GLShader : public Shader
	{
	private:
		uint m_Id;
	public:
		GLShader(ShaderType type);
		GLShader(const GLShader&) = delete;
		GLShader& operator=(const GLShader&) = delete;
		virtual ~GLShader();
	public:
		bool			LoadFromFile(const String& path);
		void			LoadFromString(const String& content);
		bool			Compile(String& log);
		uint			GetID()const;
	};
}