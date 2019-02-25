#pragma once
#include <typeinfo>
#include "RAUtils.h"
#include "ShaderProgram.h"
#include "Texture.h"
namespace RA_FRAMEWORK
{
	class Material
	{
	private:	
		KLMList<ShaderVariable<int>*> m_IntList;
		KLMList<ShaderVariable<Vec2i>*> m_V2IntList;
		KLMList<ShaderVariable<Vec3i>*> m_V3IntList;
		KLMList<ShaderVariable<Vec4i>*> m_V4IntList;
		KLMList<ShaderVariable<float>*> m_FloatList;
		KLMList<ShaderVariable<Vec2>*> m_V2FloatList;
		KLMList<ShaderVariable<Vec3>*> m_V3FloatList;
		KLMList<ShaderVariable<Vec4>*> m_V4FloatList;
		KLMList<ShaderVariable<Mat2>*> m_Mat2List;
		KLMList<ShaderVariable<Mat3>*> m_Mat3List;
		KLMList<ShaderVariable<Mat4>*> m_Mat4List;
		KLMList<ShaderVariable<Texture*>*> m_Texture2DList;
		ShaderProgram* p_Shader;
	public:
		Material(ShaderProgram* shaderProg);
		Material(const Material&) = delete;
		Material& operator=(const Material&) = delete;
		virtual ~Material();
	public:
		void Use();
		ShaderProgram* GetShaderProgram()							   { return p_Shader; }
		void AddShaderVariable(const String& name, int value)		   { m_IntList.Add(new ShaderVariable<int>(name, value));}
		void AddShaderVariable(const String& name, const Vec2i& value) { m_V2IntList.Add(new ShaderVariable<Vec2i>(name, value));}
		void AddShaderVariable(const String& name, const Vec3i& value) { m_V3IntList.Add(new ShaderVariable<Vec3i>(name, value));}
		void AddShaderVariable(const String& name, const Vec4i& value) { m_V4IntList.Add(new ShaderVariable<Vec4i>(name, value));}
		void AddShaderVariable(const String& name, float value)		   { m_FloatList.Add(new ShaderVariable<float>(name, value));}
		void AddShaderVariable(const String& name, const Vec2& value)  { m_V2FloatList.Add(new ShaderVariable<Vec2>(name, value));}
		void AddShaderVariable(const String& name, const Vec3& value)  { m_V3FloatList.Add(new ShaderVariable<Vec3>(name, value));}
		void AddShaderVariable(const String& name, const Vec4& value)  { m_V4FloatList.Add(new ShaderVariable<Vec4>(name, value));}
		void AddShaderVariable(const String& name, const Mat2& value)  { m_Mat2List.Add(new ShaderVariable<Mat2>(name, value));}
		void AddShaderVariable(const String& name, const Mat3& value)  { m_Mat3List.Add(new ShaderVariable<Mat3>(name, value));}
		void AddShaderVariable(const String& name, const Mat4& value)  { m_Mat4List.Add(new ShaderVariable<Mat4>(name, value));}
		void AddShaderVariable(const String& name, Texture* value)	   { m_Texture2DList.Add(new ShaderVariable<Texture*>(name, value));}
		//ShaderVariable* FindVariable(ShaderVariableType type, const String& name);
		//bool SetVariable(ShaderVariableType type, const String& name, void* value);
	};
}