#include "GLSkyBox.h"
#include "ImageLoader.h"
namespace RA_FRAMEWORK
{

	GLSkyBox::GLSkyBox():SkyBox(GfxAPI::GL), m_ID{0}, m_ErrorCode{""}
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
		std::vector<GLuint> faces
		{ 
			GL_TEXTURE_CUBE_MAP_POSITIVE_X, 
			GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
			
			GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 
		};
		ImageLoader loader;
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID);
		for (GLuint i = 0; i < 6; ++i)
		{
			Image img;
			String s = desc.GetFace(i);
			if (loader.Load(s,img)) //Loading file to RAM
			{
				//bool t = img.HAS_TRANSPARENCY;
				// if loaded, push file onto the GPU
				glTexImage2D(faces[i],
					0, GL_RGBA, img.GetWidth(), img.GetHeight(), 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)img.GetPixels());
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
		if (status) outStatus = "OK";
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

	bool GLSkyBox::Bind(const String& uniformName, uint shaderProgID)
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
		int slot = 0;
		glUniform1i(samplerID, slot); // assign sampler to texture unit index
		//glActiveTexture(GL_TEXTURE0 + slot);// make current texture unit active (i.e. GL_TEXTURE_2D  will refer to it)
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID);//bind texture
		return true;
	}

	GLSkyBox::~GLSkyBox()
	{
		glDeleteTextures(1, &m_ID);
	}
}