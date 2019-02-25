#pragma once
#include "RATypes.h"
namespace RA_FRAMEWORK
{
	class Texture
	{
	private:
		GfxAPI m_API;
	protected:
		Texture(GfxAPI API, unsigned id);
		unsigned m_ID;
	public:
		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;
		GfxAPI GetAPI() { return m_API; }
		virtual ~Texture();
	public:
		unsigned GetID() { return m_ID; }
	};
}