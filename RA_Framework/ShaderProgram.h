#pragma once
#include "Shader.h"
#include "Texture.h"
namespace RA_FRAMEWORK
{
	class ShaderProgram
	{
	private:
		GfxAPI m_API;
	protected:
		ShaderProgram(GfxAPI API);
	public:
		ShaderProgram(const ShaderProgram&)					= delete;
		ShaderProgram& operator=(const ShaderProgram&)		= delete;
		virtual ~ShaderProgram();
	public:
		GfxAPI GetAPI() { return m_API; }
	public:
		virtual bool	SetAsCurrent() = 0;
		virtual bool	Create() = 0;		
		virtual void	SetInt(const String& varname, int value) = 0;
		virtual void	SetFloat(const String& varname, float value) = 0;
		virtual void	SetVec2Int(const String& varname, const Vec2i& value) = 0;
		virtual void	SetVec3Int(const String& varname, const Vec3i& value) = 0;
		virtual void	SetVec4Int(const String& varname, const Vec4i& value) = 0;
		virtual void	SetVec2Float(const String& varname, const Vec2& value) = 0;
		virtual void	SetVec3Float(const String& varname, const Vec3& value) = 0;
		virtual void	SetVec4Float(const String& varname, const Vec4& value) = 0;
		virtual void	SetMat2x2(const String& varname, const Mat2& value) = 0;
		virtual void	SetMat3x3(const String& varname, const Mat3& value) = 0;
		virtual void	SetMat4x4(const String& varname, const Mat4& value) = 0;
		virtual void	SetTexture(const String& varname, Texture* texture) = 0;
	};
}