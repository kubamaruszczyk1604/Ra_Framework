#pragma once
#include "ShaderVariable.h"
namespace RA_FRAMEWORK
{
	enum class ShaderType
	{
		VERTEX = 0,
		FRAGMENT = 1
	};
	class Shader
	{
	private:
		ShaderType m_ShaderType;
		GfxAPI m_API;
	protected:
		Shader(GfxAPI api, ShaderType type);
	public:
		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;
		virtual ~Shader();
	public:
		ShaderType		GetType()	{ return m_ShaderType; }
		GfxAPI			GetAPI()	{ return m_API; }	
	};
}