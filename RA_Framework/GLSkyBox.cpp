#include "GLSkyBox.h"
#include "ImageLoader.h"
namespace RA_FRAMEWORK
{

	GLSkyBox::GLSkyBox(): m_ID{0}
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
			if (loader.Load(s,img))
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, GL_RGB, img.GetWidth(), img.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, img.GetPixels());
			}
			else
			{
				outStatus += "ERROR: Failed to load " + names[i] + " face.\n";
				status = false;
			}
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

	GLSkyBox::~GLSkyBox()
	{
		glDeleteTextures(1, &m_ID);
	}
}