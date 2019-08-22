#pragma once
#include "RATypes.h"
#include "Texture.h"
#include <iostream>
#include <fstream>
namespace RA_FRAMEWORK
{
	struct SkyBoxDesc
	{
		String RIGHT;
		String LEFT;
		String TOP;
		String BOTTOM;
		String FRONT;
		String BACK;


		String&  GetFace(uint i)
		{
			switch (i)
			{
			case 0:
				return RIGHT;
			case 1:
				return LEFT;
			case 2:
				return TOP;
			case 3:
				return BOTTOM;
			case 4:
				return FRONT;
			case 5:
				return BACK;
			default:
				return const_cast<String&>(s_ERROR);
			}
		}

	private:
		static const String s_ERROR;
		
	};

	class SkyBox
	{
	private:
		int					m_Width;
		int					m_Height;
		GfxAPI				m_API;
	protected:
		SkyBox(GfxAPI api);
	protected:
		void				SetDimensions(int x, int y);
	public:
		static bool			ReadDesc(const String& raskyFile, SkyBoxDesc& outDesc);
		virtual ~SkyBox()	{}
	public:
		virtual bool		Load(const String& raskyFile, String& outStatus) = 0;
		virtual void		Bind() = 0;
		virtual void		Unbind() = 0;
	    virtual void		GenerateMipmaps() = 0;
		virtual void		SetWrapMode(TextureWrapMode mode) = 0;
		virtual void		SetMinFilterMode(TextureFilterMode filterMode) = 0;
		virtual void		SetMagFilterMode(TextureFilterMode filterMode) = 0;
		virtual void		SetFilterMode(TextureFilterMode minMode, TextureFilterMode magMode) = 0;
		virtual uint		GetMipmapLevel() = 0;
	public:
		int					Width()		{ return m_Width;	 }
		int					Height()	{ return m_Height;	 }
		GfxAPI				GetApi()	{ return m_API;		 }

	};

	

}