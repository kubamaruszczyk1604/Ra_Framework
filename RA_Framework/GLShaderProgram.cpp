#include "GLShaderProgram.h"
namespace RA_FRAMEWORK
{
	GLShaderProgram::GLShaderProgram(GLShader * vertexShader, GLShader * fragmentShader) :
		ShaderProgram(GfxAPI::GL),
		p_VertexShader{ vertexShader },
		p_FragmentShader{ fragmentShader }
	{
		Create();
	}

	GLShaderProgram::~GLShaderProgram()
	{
		if (p_VertexShader) glDetachShader(m_ProgId, p_VertexShader->GetID());
		if (p_FragmentShader) glDetachShader(m_ProgId, p_FragmentShader->GetID());
		glDeleteProgram(m_ProgId);
	}

	bool GLShaderProgram::Create()
	{
		if (m_Created) return true;
		m_ProgId = glCreateProgram();
		glAttachShader(m_ProgId, p_VertexShader->GetID());
		glAttachShader(m_ProgId, p_FragmentShader->GetID());
		glLinkProgram(m_ProgId);
		int ok = 0;
		glGetProgramiv(m_ProgId, GL_LINK_STATUS, &ok);
		m_Created = (ok != GL_FALSE);
		return true;
	}

	bool GLShaderProgram::SetAsCurrent()
	{
		if (p_VertexShader&&p_FragmentShader)
		{
			glUseProgram(m_ProgId);
			return true;
		}
		return false;
	}

	void GLShaderProgram::SetInt(const String & varname, int value)
	{
		GLuint loc = glGetUniformLocation(m_ProgId, varname.c_str());
		glUniform1i(loc, value);
	}

	void GLShaderProgram::SetFloat(const String & varname, float value)
	{
		GLuint loc = glGetUniformLocation(m_ProgId, varname.c_str());
		glUniform1f(loc, value);
	}

	void GLShaderProgram::SetVec2Int(const String & varname, const Vec2i& value)
	{
		GLuint loc = glGetUniformLocation(m_ProgId, varname.c_str());
		glUniform2i(loc, value.x, value.y);
		//glUniform2iv(loc,2, &value.x);
	}

	void GLShaderProgram::SetVec3Int(const String & varname, const Vec3i & value)
	{
		GLuint loc = glGetUniformLocation(m_ProgId, varname.c_str());
		glUniform3i(loc, value.x, value.y, value.z);
	}

	void GLShaderProgram::SetVec4Int(const String & varname, const Vec4i & value)
	{
		GLuint loc = glGetUniformLocation(m_ProgId, varname.c_str());
		glUniform4i(loc, value.x, value.y, value.z, value.w);
	}

	void GLShaderProgram::SetVec2Float(const String & varname, const Vec2 & value)
	{
		GLuint loc = glGetUniformLocation(m_ProgId, varname.c_str());
		glUniform2f(loc, value.x, value.y);
	}

	void GLShaderProgram::SetVec3Float(const String & varname, const Vec3 & value)
	{
		GLuint loc = glGetUniformLocation(m_ProgId, varname.c_str());
		glUniform3fv(loc, 1, &value.x);
	}

	void GLShaderProgram::SetVec4Float(const String & varname, const Vec4 & value)
	{
		GLuint loc = glGetUniformLocation(m_ProgId, varname.c_str());
		glUniform4f(loc, value.x, value.y, value.z, value.w);
	}

	void GLShaderProgram::SetMat2x2(const String & varname, const Mat2 & value)
	{
		GLuint loc = glGetUniformLocation(m_ProgId, varname.c_str());
		glUniformMatrix2fv(loc, 1, GL_FALSE, &value[0][0]);
	}

	void GLShaderProgram::SetMat3x3(const String & varname, const Mat3 & value)
	{
		GLuint loc = glGetUniformLocation(m_ProgId, varname.c_str());
		glUniformMatrix3fv(loc, 1, GL_FALSE, &value[0][0]);
	}

	void GLShaderProgram::SetMat4x4(const String & varname, const Mat4 & value)
	{
		GLuint loc = glGetUniformLocation(m_ProgId, varname.c_str());
		glUniformMatrix4fv(loc, 1, GL_FALSE, &value[0][0]);
	}

	void GLShaderProgram::SetTexture(const String & varname, int textureID)
	{
		GLuint samplerID = glGetUniformLocation(m_ProgId, varname.c_str());
		glUniform1i(samplerID, textureID);
	}
}
