#pragma once
#include "ShaderProgram.h"
#include "GLShader.h"
namespace RA_FRAMEWORK
{
	class GLShaderProgram: public ShaderProgram
	{

	private:
		GLuint m_ProgId;
		GLShader* p_VertexShader;
		GLShader* p_FragmentShader;
		bool m_Created{ false };


	public:
		GLShaderProgram(GLShader* vertexShader, GLShader* fragmentShader);
		virtual ~GLShaderProgram();

		GLShaderProgram& operator=(GLShaderProgram&) = delete;
		GLShaderProgram(const GLShaderProgram&) = delete;

		bool Create() override;
		bool SetAsCurrent() override;
		GLuint GetID() { return m_ProgId; }


		void SetInt(const String& varname, int value) override;
		void SetFloat(const String& varname, float value) override;

		void SetVec2Int(const String& varname, const Vec2i& value) override;
		void SetVec3Int(const String& varname, const Vec3i& value) override;
		void SetVec4Int(const String& varname, const Vec4i& value) override;

		void SetVec2Float(const String& varname, const Vec2& value) override;
		void SetVec3Float(const String& varname, const Vec3& value) override;
		void SetVec4Float(const String& varname, const Vec4& value) override;

		void SetMat2x2(const String& varname, const Mat2& value) override;
		void SetMat3x3(const String& varname, const Mat3& value) override;
		void SetMat4x4(const String& varname, const Mat4& value) override;

		void SetTexture(const String& varname, int textureID) override;
	};

}
