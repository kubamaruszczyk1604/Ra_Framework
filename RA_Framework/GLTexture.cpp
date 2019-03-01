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
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, TEX_FORMAT_LUT_GL[(uint)format], data);
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
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, TEX_FORMAT_LUT_GL[(uint)format], data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TEX_FILTER_LUT_GL[0]);// nearest
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TEX_FILTER_LUT_GL[0]);// nearest
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TEX_ADDRESS_MODE_LUT_GL[0]);// wrap
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TEX_ADDRESS_MODE_LUT_GL[0]);// wrap
	}

	GLTexture::GLTexture(TextureFormat format, Image& image):
		Texture(GfxAPI::GL, 0, 0),
		c_Width(image.GetWidth()),
		c_Height(image.GetHeight())
	{
		GLenum form = image.HAS_TRANSPARENCY ? GL_BGRA : GL_BGR;
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, c_Width, c_Height, 0, form, TEX_FORMAT_LUT_GL[(uint)format], (void*)image.GetPixels());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TEX_FILTER_LUT_GL[4]);// nearest
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TEX_FILTER_LUT_GL[4]);// nearest
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TEX_ADDRESS_MODE_LUT_GL[0]);// wrap
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TEX_ADDRESS_MODE_LUT_GL[0]);// wrap


		glGenerateMipmap(GL_TEXTURE_2D);
		//glGenerateTextureMipmap(m_ID);
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
		glActiveTexture(GL_TEXTURE0 + m_Slot);
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}

	void GLTexture::Bind(const String& uniformName, uint shaderProgID)
	{
		// This function:
		//1 binds shader sampler to texture unit of index "slot"
		//2 binds textureID to texture unit of index "slot"

		GLuint samplerID = glGetUniformLocation(shaderProgID, uniformName.c_str());
		glUniform1i(samplerID, m_Slot); // assign sampler to texture unit index
		glActiveTexture(GL_TEXTURE0 + m_Slot);// make current texture unit active (ie. GL_TEXTURE_2D  will refer to it)
		glBindTexture(GL_TEXTURE_2D, m_ID);//bind texture
	}

	void GLTexture::Unbind()
	{
		glActiveTexture(GL_TEXTURE0 + m_Slot);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	GLTexture::~GLTexture()
	{
		glDeleteTextures(1, &m_ID);
	}
}