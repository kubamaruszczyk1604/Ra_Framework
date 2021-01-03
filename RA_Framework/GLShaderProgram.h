#pragma once
#include "ShaderProgram.h"
#include "GLShader.h"
#include "GLSkyBox.h"
namespace RA_FRAMEWORK
{
	class GLShaderProgram: public ShaderProgram
	{
	private:
		GLuint					m_ProgId;
		const GLShader*			p_VertexShader;
		const GLShader*			p_FragmentShader;
		bool					m_Created{ false };
	public:
		GLShaderProgram(GLShader* vertexShader, GLShader* fragmentShader);
		GLShaderProgram& operator=(GLShaderProgram&)				= delete;
		GLShaderProgram(const GLShaderProgram&)						= delete;
		virtual ~GLShaderProgram();
	public:
		uint		GetID()const		{ return m_ProgId; }
		bool		Created()const		{ return m_Created; }
	public:
		bool		Create()override;
		bool		SetAsCurrent()override;
	public:
		void		SetInt(const String& varname, int value)override;
		void		SetFloat(const String& varname, float value)override;
		void		SetVec2Int(const String& varname, const Vec2i& value)override;
		void		SetVec3Int(const String& varname, const Vec3i& value)override;
		void		SetVec4Int(const String& varname, const Vec4i& value)override;
		void		SetVec2Float(const String& varname, const Vec2& value)override;
		void		SetVec3Float(const String& varname, const Vec3& value)override;
		void		SetVec4Float(const String& varname, const Vec4& value)override;
		void		SetMat2x2(const String& varname, const Mat2& value)override;
		void		SetMat3x3(const String& varname, const Mat3& value)override;
		void		SetMat4x4(const String& varname, const Mat4& value)override;
		void		SetTexture(const String& varname, Texture* texture)override;
		void		SetCubeTexture(const String& varname, SkyBox* skybox)override;
	};
}
