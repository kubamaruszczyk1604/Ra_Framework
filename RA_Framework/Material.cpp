#include "Material.h"
namespace RA_FRAMEWORK
{
	Material::Material(ShaderProgram* shaderProg):
		p_Shader(shaderProg), m_TextureCounter{0} {}

	Material::~Material()
	{
		for (int i = 0; i < m_IntList.Count(); ++i)
		{
			delete m_IntList[i];
		}
		for (int i = 0; i < m_V2IntList.Count(); ++i)
		{
			delete m_V2IntList[i];
		}
		for (int i = 0; i < m_V3IntList.Count(); ++i)
		{
			delete m_V3IntList[i];
		}
		for (int i = 0; i < m_V4IntList.Count(); ++i)
		{
			delete m_V4IntList[i];
		}
		for (int i = 0; i < m_FloatList.Count(); ++i)
		{
			delete m_FloatList[i];
		}
		for (int i = 0; i < m_V2FloatList.Count(); ++i)
		{
			delete m_V2FloatList[i];
		}
		for (int i = 0; i < m_V3FloatList.Count(); ++i)
		{
			delete (m_V3FloatList)[i];
		}
		for (int i = 0; i < m_V4FloatList.Count(); ++i)
		{
			delete m_V4FloatList[i];
		}
		for (int i = 0; i < m_Mat2List.Count(); ++i)
		{
			delete m_Mat2List[i];
		}
		for (int i = 0; i < m_Mat3List.Count(); ++i)
		{
			delete m_Mat3List[i];
		}
		for (int i = 0; i < m_Mat4List.Count(); ++i)
		{
			delete m_Mat4List[i];
		}
		for (int i = 0; i < m_Texture2DList.Count(); ++i)
		{
			delete m_Texture2DList[i];
		}
	}

	void Material::Use()
	{
		p_Shader->SetAsCurrent();

		for (int i = 0; i < m_IntList.Count(); ++i)
		{
			auto temp = m_IntList[i];
			p_Shader->SetInt(temp->GetName(),temp->GetData());
		}
		for (int i = 0; i < m_V2IntList.Count(); ++i)
		{
			auto temp = m_V2IntList[i];
			p_Shader->SetVec2Int(temp->GetName(), temp->GetData());
		}
		for (int i = 0; i < m_V3IntList.Count(); ++i)
		{
			auto temp = m_V3IntList[i];
			p_Shader->SetVec3Int(temp->GetName(), temp->GetData());
		}
		for (int i = 0; i < m_V4IntList.Count(); ++i)
		{
			auto temp = m_V4IntList[i];
			p_Shader->SetVec4Int(temp->GetName(), temp->GetData());
		}
		for (int i = 0; i < m_FloatList.Count(); ++i)
		{
			auto temp = m_FloatList[i];
			p_Shader->SetFloat(temp->GetName(), temp->GetData());
		}
		for (int i = 0; i < m_V2FloatList.Count(); ++i)
		{
			auto temp = m_V2FloatList[i];
			p_Shader->SetVec2Float(temp->GetName(), temp->GetData());
		}
		for (int i = 0; i < m_V3FloatList.Count(); ++i)
		{
			auto temp = m_V3FloatList[i];
			p_Shader->SetVec3Float(temp->GetName(), temp->GetData());
		}
		for (int i = 0; i < m_V4FloatList.Count(); ++i)
		{
			auto temp = m_V4FloatList[i];
			p_Shader->SetVec4Float(temp->GetName(), temp->GetData());
		}
		for (int i = 0; i < m_Mat2List.Count(); ++i)
		{
			auto temp = m_Mat2List[i];
			p_Shader->SetMat2x2(temp->GetName(), temp->GetData());
		}
		for (int i = 0; i < m_Mat3List.Count(); ++i)
		{
			auto temp = m_Mat3List[i];
			p_Shader->SetMat3x3(temp->GetName(), temp->GetData());
		}
		for (int i = 0; i < m_Mat4List.Count(); ++i)
		{
			auto temp = m_Mat4List[i];
			p_Shader->SetMat4x4(temp->GetName(), temp->GetData());
		}
		for (int i = 0; i < m_Texture2DList.Count(); ++i)
		{
			auto temp = m_Texture2DList[i];
			p_Shader->SetTexture(temp->GetName(), temp->GetData());
			
		}
	}
	void Material::UnbindTextures()
	{
		for (int i = 0; i < m_Texture2DList.Count(); ++i)
		{
			auto temp = m_Texture2DList[i];
			temp->GetData()->Unbind();
		}
	}
	//ShaderVariable* Material::FindVariable(ShaderVariableType type, const String& name)
	//{
	//	ShaderVariable** sw = m_Variables.Find([name, type](ShaderVariable* const& Object) { return ((Object->GetName() == name) && (Object->GetType() == type)); });
	//	return (*sw);
	//}

	//bool Material::SetVariable(ShaderVariableType type, const String& name, void* value)
	//{
	//	ShaderVariable* tempPtr = this->FindVariable(type, name);
	//	if (tempPtr == nullptr) { return false; }
	//	tempPtr->SetValue(value);
	//	return true;
	//}
}