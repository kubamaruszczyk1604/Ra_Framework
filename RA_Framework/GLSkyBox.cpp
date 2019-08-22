#include "GLSkyBox.h"
#include "ImageLoader.h"
namespace RA_FRAMEWORK
{

	GLSkyBox::GLSkyBox():SkyBox(GfxAPI::GL), m_ID{0}
	{
	}

	bool GLSkyBox::Load(const String& raskyFile, String & outStatus)
	{
		// Description part
		SkyBoxDesc desc;
		if (!SkyBox::ReadDesc(raskyFile, desc))
		{
			outStatus = "ERROR: Failed to read rasky file.";
			return false;
		}
		bool status = true;
		std::vector<String> names{ "right", "left", "top", "bottom", "front", "back" };
		ImageLoader loader;
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID);
		for (int i = 0; i < 6; ++i)
		{
			Image img;
			String s = desc.GetFace(i);
			if (loader.Load(s,img)) //Loading file to RAM
			{
				// if loaded, push file onto the GPU
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, GL_RGB, img.GetWidth(), img.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, img.GetPixels());
			}
			else
			{
				// if failed to load, set error code
				outStatus += "ERROR: Failed to load " + names[i] + " face.\n";
				status = false;
			}
			if (i == 0) SetDimensions(img.GetWidth(), img.GetHeight());
			// free image from ram
			loader.Free(img);

		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		return status;
	}

	void GLSkyBox::Bind()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID);
	}

	void GLSkyBox::Unbind()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	void GLSkyBox::GenerateMipmaps()
	{
	}

	void GLSkyBox::SetWrapMode(TextureWrapMode mode)
	{
	}

	void GLSkyBox::SetMinFilterMode(TextureFilterMode filterMode)
	{
	}

	void GLSkyBox::SetMagFilterMode(TextureFilterMode filterMode)
	{
	}

	void GLSkyBox::SetFilterMode(TextureFilterMode minMode, TextureFilterMode magMode)
	{
	}

	uint GLSkyBox::GetMipmapLevel()
	{
		return uint();
	}

	GLSkyBox::~GLSkyBox()
	{
		glDeleteTextures(1, &m_ID);
	}
}