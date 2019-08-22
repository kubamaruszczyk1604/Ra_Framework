#pragma once
#include "SkyBox.h"
namespace RA_FRAMEWORK
{
	class GLSkyBox : public SkyBox
	{
	private:
		GLuint		m_ID;
	public:
		GLSkyBox();
		virtual ~GLSkyBox();
	public:
		
		bool		Load(const String& raskyFile, String& outStatus);
		void		Bind()override;
		void		Unbind()override;
		void		GenerateMipmaps();
		void		SetWrapMode(TextureWrapMode mode)override;
		void		SetMinFilterMode(TextureFilterMode filterMode)override;
		void		SetMagFilterMode(TextureFilterMode filterMode)override;
		void		SetFilterMode(TextureFilterMode minMode, TextureFilterMode magMode)override;
		uint		GetMipmapLevel()override;
	};

}