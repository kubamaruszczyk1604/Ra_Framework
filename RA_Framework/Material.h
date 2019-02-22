#pragma once

#include "RAUtils.h"
#include "ShaderProgram.h"
#include "Texture.h"
namespace RA_FRAMEWORK
{

	class Material
	{

	private:	
		KLMList<ShaderVariable*> m_Variables;
		ShaderProgram* p_Shader;
	public:
		Material(ShaderProgram* shaderProg);
		Material(const Material&) = delete;
		Material& operator=(const Material&) = delete;
		virtual ~Material();

		void Use();
		ShaderProgram* GetShaderProgram() { return p_Shader; }
		void AddShaderVariable(ShaderVariableType type, const String& name);
		void AddShaderVariable(ShaderVariableType type, const String& name, void* value);
		ShaderVariable* FindVariable(ShaderVariableType type, const String& name);
		bool SetVariable(ShaderVariableType type, const String& name, void* value);
	};

}