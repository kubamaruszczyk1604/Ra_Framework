#include "GLTexture.h"
namespace RA_FRAMEWORK
{
	
	//www.opengl-tutorial.org/intermediate-tutorials/tutorial-14-render-to-texture/
	GLTexture::GLTexture(int w, int h, const TextureFormatDescriptor& desc, void* data) :
		Texture(GfxAPI::GL, 0, 0),
		c_Width(w),
		c_Height(h)
	{
		this->SetTextureDescriptor(desc);
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);
		glTexImage2D(GL_TEXTURE_2D, 0,
			TEX_INTERNAL_DATA_FORMAT_LUT_GL[static_cast<uint>(desc.TEXTURE_DATA_FORMAT)],
			w, h, 0,
			PIXEL_DATA_FORMAT_LUT_GL[static_cast<uint>(desc.INPUT_PIXEL_FORMAT)],
			PIXEL_DATA_TYPE_LUT_GL[(uint)desc.INPUT_DATA_TYPE], data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TEX_FILTER_LUT_GL[static_cast<uint>(desc.MIN_FILTER_MODE)]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TEX_FILTER_LUT_GL[static_cast<uint>(desc.MAG_FILTER_MODE)]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TEX_ADDRESS_MODE_LUT_GL[static_cast<uint>(desc.WRAP_MODE)]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TEX_ADDRESS_MODE_LUT_GL[static_cast<uint>(desc.WRAP_MODE)]);
		if(desc.GEN_MIPMAPS)glGenerateMipmap(GL_TEXTURE_2D);
		//s_TextureUnitCounter++;
	}

	GLTexture::GLTexture(int w, int h, const TextureFormatDescriptor & desc): 
		GLTexture(w,h,desc,nullptr){}

	GLTexture::GLTexture(InputPixelDataType inputPixelDataType, TextureDataFormat internalFormat, Image& image):
		Texture(GfxAPI::GL, 0, 0),
		c_Width(image.GetWidth()),
		c_Height(image.GetHeight())
	{
		GLenum form = image.HAS_TRANSPARENCY ? GL_BGRA : GL_BGR;
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);
		glTexImage2D(GL_TEXTURE_2D, 0, TEX_INTERNAL_DATA_FORMAT_LUT_GL[static_cast<uint>(internalFormat)],
			 c_Width, c_Height, 0, form,
			PIXEL_DATA_TYPE_LUT_GL[(uint)inputPixelDataType], (void*)image.GetPixels());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TEX_FILTER_LUT_GL[1]);// nearest
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TEX_FILTER_LUT_GL[1]);// nearest
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TEX_ADDRESS_MODE_LUT_GL[0]);// wrap
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TEX_ADDRESS_MODE_LUT_GL[0]);// wrap
		glGenerateMipmap(GL_TEXTURE_2D);
		TextureFormatDescriptor desc;
		desc.MAG_FILTER_MODE = TextureFilterMode::NEAREST;
		desc.MIN_FILTER_MODE = TextureFilterMode::NEAREST;
		desc.WRAP_MODE = TextureWrapMode::WRAP;
		desc.GEN_MIPMAPS = true;
		desc.TEXTURE_DATA_FORMAT = internalFormat;
		desc.INPUT_DATA_TYPE = inputPixelDataType;
		desc.INPUT_PIXEL_FORMAT = image.HAS_TRANSPARENCY ? InputPixelFormat::BGRA : InputPixelFormat::BGR;

		
		//s_TextureUnitCounter++;
	}

	GLTexture::GLTexture(TextureDataFormat internalFormat, Image& image):
		GLTexture(InputPixelDataType::UNISGNED_BYTE, internalFormat, image){}

	GLTexture::GLTexture(int w, int h):
		Texture(GfxAPI::GL, 0, 0, true),
		c_Width(w),
		c_Height(h)
	{	
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, w, h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		TextureFormatDescriptor desc;
		desc.MAG_FILTER_MODE = TextureFilterMode::NEAREST;
		desc.MIN_FILTER_MODE = TextureFilterMode::NEAREST;
		desc.WRAP_MODE = TextureWrapMode::CLAMP;
		desc.GEN_MIPMAPS = false;
		desc.TEXTURE_DATA_FORMAT = TextureDataFormat::DEPTH_COMPONENT;
		desc.INPUT_DATA_TYPE = InputPixelDataType::FLOAT;
		desc.INPUT_PIXEL_FORMAT = InputPixelFormat::DEPTH_COMPONENT;
		this->SetTextureDescriptor(desc);
	}

	GLTexture * GLTexture::GenerateDepthTexture(int w, int h)
	{
		return new GLTexture(w, h);
	}

	GLTexture::GLTexture(Image& image):
		GLTexture(InputPixelDataType::UNISGNED_BYTE,TextureDataFormat::RGBA,image){}

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

	bool GLTexture::Bind(const String& uniformName, uint shaderProgID)
	{
		// This function:
		//1 binds shader sampler to texture unit of index "slot"
		//2 binds textureID to texture unit of index "slot"

		int samplerID = glGetUniformLocation(shaderProgID, uniformName.c_str());
		if (samplerID == -1)
		{
			m_ErrorCode = 1; 
			return false; 
		}
		glUniform1i(samplerID, m_Slot); // assign sampler to texture unit index
		glActiveTexture(GL_TEXTURE0 + m_Slot);// make current texture unit active (ie. GL_TEXTURE_2D  will refer to it)
		glBindTexture(GL_TEXTURE_2D, m_ID);//bind texture
		return true;
	}

	void GLTexture::Unbind()
	{
		glActiveTexture(GL_TEXTURE0 + m_Slot);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void GLTexture::GenerateMipmaps()
	{
		this->Bind();
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	void GLTexture::SetWrapMode(TextureWrapMode mode)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TEX_ADDRESS_MODE_LUT_GL[static_cast<uint>(mode)]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TEX_ADDRESS_MODE_LUT_GL[static_cast<uint>(mode)]);
	}

	void GLTexture::SetMinFilterMode(TextureFilterMode filterMode)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TEX_FILTER_LUT_GL[static_cast<uint>(filterMode)]);
	}

	void GLTexture::SetMagFilterMode(TextureFilterMode filterMode)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TEX_FILTER_LUT_GL[static_cast<uint>(filterMode)]);
	}

	void GLTexture::SetFilterMode(TextureFilterMode minMode, TextureFilterMode magMode)
	{	
		this->SetMinFilterMode(minMode);
		this->SetMagFilterMode(magMode);
	}

	unsigned GLTexture::GetMipmapLevel()
	{
		return 0;
	}

	GLTexture::~GLTexture()
	{
		glDeleteTextures(1, &m_ID);
	}
}