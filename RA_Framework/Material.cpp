#include "Material.h"

namespace RA_FRAMEWORK
{

	Material::Material(ShaderProgram* shaderProg):
		p_Shader(shaderProg)

	{
	}

	Material::~Material()
	{
	}

	void Material::AddShaderVariable(ShaderVariableType type, const String& name)
	{
		m_Variables.Add(ShaderVariable(type, name));
	}

	void Material::AddShaderVariable(ShaderVariableType type, const String& name, void* value)
	{
		m_Variables.Add(ShaderVariable(type, name, value));
	}

	ShaderVariable* Material::FindVariable(ShaderVariableType type, const String& name)
	{
		return m_Variables.Find([name, type](ShaderVariable const& Object) { return ((Object.GetName()==name) && (Object.GetType()==type)); });	
	}

	bool Material::SetVariable(ShaderVariableType type, const String& name, void* value)
	{
		ShaderVariable* tempPtr = this->FindVariable(type, name);
		if (tempPtr == nullptr) { return false; }
		tempPtr->SetValue(value);
		return true;
	}
}