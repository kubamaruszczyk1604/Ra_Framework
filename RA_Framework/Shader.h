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
		const ShaderType		m_ShaderType;
		const GfxAPI			m_API;
	protected:
		Shader(GfxAPI api, ShaderType type);
	public:
		Shader(const Shader&)					= delete;
		Shader& operator=(const Shader&)		= delete;
		virtual ~Shader();
	public:
		ShaderType		GetType()const	{ return m_ShaderType; }
		GfxAPI			GetAPI()const	{ return m_API; }	
	};
}