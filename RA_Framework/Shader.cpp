#include "Shader.h"

namespace RA_FRAMEWORK
{



	Shader::Shader(GfxAPI api, ShaderType type) :
		m_API{ api }, m_ShaderType{ type }
	{

	}

	Shader::~Shader()
	{
	}
}
