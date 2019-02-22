#include "Material.h"

namespace RA_FRAMEWORK
{

	Material::Material(ShaderProgram* shaderProg):
		p_Shader(shaderProg)

	{
	}

	Material::~Material()
	{
		for (int i = 0; i < m_Variables.Count(); ++i)
		{
			delete m_Variables[i];
		}
		m_Variables.Clear();
	}

	void Material::Use()
	{
		p_Shader->SetAsCurrent();
	}

	void Material::AddShaderVariable(ShaderVariableType type, const String& name)
	{
		m_Variables.Add(new ShaderVariable(type, name));
	}

	void Material::AddShaderVariable(ShaderVariableType type, const String& name, void* value)
	{
		m_Variables.Add(new ShaderVariable(type, name, value));
	}

	ShaderVariable* Material::FindVariable(ShaderVariableType type, const String& name)
	{
		ShaderVariable** sw = m_Variables.Find([name, type](ShaderVariable* const& Object) { return ((Object->GetName() == name) && (Object->GetType() == type)); });
		return (*sw);
	}

	bool Material::SetVariable(ShaderVariableType type, const String& name, void* value)
	{
		ShaderVariable* tempPtr = this->FindVariable(type, name);
		if (tempPtr == nullptr) { return false; }
		tempPtr->SetValue(value);
		return true;
	}
}