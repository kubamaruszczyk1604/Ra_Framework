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
	template<class T>
	class ShaderVariable
	{
	private:
		const String m_Name;
		T m_Data;
	public:
		ShaderVariable(const String& name, const T& data) :m_Name{ name }, m_Data{ data }{}
		ShaderVariable(const ShaderVariable&) = delete;
		ShaderVariable& operator=(const ShaderVariable&) = delete;
		~ShaderVariable() {}
	public:
		void				SetData(const T& data)	{ m_Data = data; }
		const T&			GetData()				{ return m_Data; }
		const String&		GetName()const			{ return m_Name; }
	};
}