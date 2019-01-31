#include "GLTexture.h"
namespace RA_FRAMEWORK
{
	const GLuint GLTexture::s_TextureAddresModeLookupTable[5] =
	{	
		GL_REPEAT,
		GL_MIRRORED_REPEAT,
		GL_CLAMP,
		GL_CLAMP_TO_BORDER,
		GL_MIRROR_CLAMP_TO_EDGE
	};


	GLTexture::GLTexture(int w, int h, TextureFormat format, void* data, TextureFilterMode minFilterMode, TextureAddressMode magFilterMode, TextureAddressMode addressMode)
	{
		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, w, h, 0, GL_RGB, static_cast<GLuint>(format), data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLuint>(minFilterMode));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLuint>(magFilterMode));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s_TextureAddresModeLookupTable[static_cast<GLuint>(addressMode)]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, s_TextureAddresModeLookupTable[static_cast<GLuint>(addressMode)]);

	}

	//www.opengl-tutorial.org/intermediate-tutorials/tutorial-14-render-to-texture/

	GLTexture::GLTexture(int w, int h, TextureFormat format, void* data)
	{
		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, w, h, 0, GL_RGB, static_cast<GLuint>(format), data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLuint>(TextureFilterMode::NEAREST));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLuint>(TextureFilterMode::NEAREST));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s_TextureAddresModeLookupTable[static_cast<GLuint>(TextureAddressMode::WRAP)]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, s_TextureAddresModeLookupTable[static_cast<GLuint>(TextureAddressMode::WRAP)]);
	}

	GLTexture::GLTexture(int w, int h, TextureFormat format)
	{
		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, w, h, 0, GL_RGB, static_cast<GLuint>(format), 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLuint>(TextureFilterMode::NEAREST));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLuint>(TextureFilterMode::NEAREST));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s_TextureAddresModeLookupTable[static_cast<GLuint>(TextureAddressMode::WRAP)]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, s_TextureAddresModeLookupTable[static_cast<GLuint>(TextureAddressMode::WRAP)]);
	}

	void GLTexture::Bind(GLuint slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

	void GLTexture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

	void GLTexture::Bind(const std::string& uniformName, GLuint shaderProgID, GLuint slot)
	{
		GLuint samplerID = glGetUniformLocation(shaderProgID, uniformName.c_str());
		glUniform1i(samplerID, slot);
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

	void GLTexture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	GLTexture::~GLTexture()
	{
		glDeleteTextures(1, &m_TextureID);
	}
}