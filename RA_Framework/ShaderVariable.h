#pragma once
#include "RATypes.h"
namespace RA_FRAMEWORK
{
	enum class ShaderVariableType
	{
		INT = 0,
		VECi2 = 1,
		VECi3 = 2,
		VECi4 = 3,

		FLOAT = 4,
		VECf2 = 5,
		VECf3 = 6,
		VECf4 = 7,

		MAT2x2 = 8,
	    MAT3x3 = 9,
		MAT4x4 = 10,

		TEXTURE1D = 11,
		TEXTURE2D = 12,
		SKYBOX = 13
	};

	
	class ShaderVariable
	{

	private:
		String m_Name;
		ShaderVariableType m_Type;
		void* m_pData;

	public:
		ShaderVariable(ShaderVariableType type, const String& name);
		ShaderVariable(ShaderVariableType type, const String& name, void* value);
		//ShaderVariable(const ShaderVariable&) = delete;
		ShaderVariable& operator=(const ShaderVariable&) = delete;
		~ShaderVariable();
		//Takes ownership only of types that are not handled by Resource Manager
		void SetValue(void* value) { m_pData = value; }
		void* GetValue() const { return m_pData; }
		ShaderVariableType GetType() const { return m_Type; }
		const String& GetName() const { return m_Name; }
	};

}