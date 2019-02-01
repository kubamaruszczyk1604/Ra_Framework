#pragma once
#include "Shader.h"
namespace RA_FRAMEWORK
{
	class ShaderProgram
	{
	private:
		GfxAPI m_API;
	protected:
		ShaderProgram(GfxAPI API);
	public:
		
		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;
		virtual bool SetAsCurrent() = 0;
		virtual bool Create() = 0;
		GfxAPI GetAPI() { return m_API; }
		virtual ~ShaderProgram();
	};

}