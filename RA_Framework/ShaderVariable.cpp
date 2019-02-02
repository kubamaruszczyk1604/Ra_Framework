#include "ShaderVariable.h"

namespace RA_FRAMEWORK
{

	ShaderVariable::ShaderVariable(ShaderVariableType type, const String& name):
		m_Type(type),m_Name(name)
	{
	}

	ShaderVariable::ShaderVariable(ShaderVariableType type, const String & name, void* value):
		m_Type(type), m_Name(name), m_pData(value)
	{
	}


	ShaderVariable::~ShaderVariable()
	{
		if ((int)m_Type < 11)
		{
			delete m_pData;
		}
	}
}