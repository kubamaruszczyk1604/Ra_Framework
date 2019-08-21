#pragma once
#include "SkyBox.h"
namespace RA_FRAMEWORK
{
	class GLSkyBox : public SkyBox
	{
	private:
		GLuint m_ID;
	public:
		GLSkyBox();
		bool Load(const String& raskyFile, String& outStatus);
		void Bind()override;
		void Unbind()override;
		virtual ~GLSkyBox();
	};

}