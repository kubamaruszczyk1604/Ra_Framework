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
		std::cout << "Konstruktora: " <<std::endl;
	}


	ShaderVariable::~ShaderVariable()
	{
		if ((int)m_Type < 11)
		{
			if (m_Type == ShaderVariableType::VECf2)
			{
				Vec2* tmp = (Vec2*)m_pData;
				delete tmp;
			}
			else if (m_Type == ShaderVariableType::VECf3)
			{
				Vec3* tmp = (Vec3*)m_pData;
				delete tmp;
			}
			else if (m_Type == ShaderVariableType::VECf4)
			{
				Vec4* tmp = (Vec4*)m_pData;
				delete tmp;
			}
			m_pData = nullptr;
		}
	}
}