#include "GLTexture.h"
namespace RA_FRAMEWORK
{
	GLTexture::GLTexture(int w, int h, TextureFormat format, void* data, TextureFilterMode minFilterMode, TextureAddressMode magFilterMode, TextureAddressMode addressMode) :
		Texture(GfxAPI::GL,0,0),
		c_Width(w),
		c_Height(h)
	{
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR, TEX_FORMAT_LUT_GL[(uint)format], data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TEX_FILTER_LUT_GL[static_cast<uint>(minFilterMode)]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TEX_FILTER_LUT_GL[static_cast<uint>(magFilterMode)]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TEX_ADDRESS_MODE_LUT_GL[static_cast<uint>(addressMode)]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TEX_ADDRESS_MODE_LUT_GL[static_cast<uint>(addressMode)]);
	}
	//www.opengl-tutorial.org/intermediate-tutorials/tutorial-14-render-to-texture/
	GLTexture::GLTexture(int w, int h, TextureFormat format, void* data):
		Texture(GfxAPI::GL,0,0),
		c_Width(w),
		c_Height(h)
	{
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR, TEX_FORMAT_LUT_GL[(uint)format], data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TEX_FILTER_LUT_GL[0]);// nearest
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TEX_FILTER_LUT_GL[0]);// nearest
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TEX_ADDRESS_MODE_LUT_GL[0]);// wrap
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TEX_ADDRESS_MODE_LUT_GL[0]);// wrap
	}

	GLTexture::GLTexture(int w, int h, TextureFormat format):
		Texture(GfxAPI::GL, 0, 0),
		c_Width(w),
		c_Height(h)
	{
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, TEX_FORMAT_LUT_GL[(uint)format], nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TEX_FILTER_LUT_GL[0]);// nearest
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TEX_FILTER_LUT_GL[0]);// neatest
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TEX_ADDRESS_MODE_LUT_GL[0]);// wrap
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TEX_ADDRESS_MODE_LUT_GL[0]);// wrap
	}

	void GLTexture::Bind(uint slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}

	void GLTexture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}

	void GLTexture::Bind(const String& uniformName, uint shaderProgID, uint slot)
	{
		const uint samplerID = glGetUniformLocation(shaderProgID, uniformName.c_str());
		glUniform1i(samplerID, slot);
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}

	void GLTexture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	GLTexture::~GLTexture()
	{
		glDeleteTextures(1, &m_ID);
	}
}