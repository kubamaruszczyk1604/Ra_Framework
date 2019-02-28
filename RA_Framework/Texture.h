#pragma once
#include "RATypes.h"
namespace RA_FRAMEWORK
{
	class Texture
	{
	private:
		const GfxAPI m_API;
	protected:
		Texture(GfxAPI API, unsigned id, unsigned slot);
		unsigned m_ID;
		unsigned m_Slot;
	public:
		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;
		GfxAPI GetAPI() { return m_API; }
		virtual ~Texture();
	public:
		inline unsigned GetID()const 				{ return m_ID; }
		inline unsigned GetSlot()const				{ return m_Slot; }
		inline void SetSlot(const unsigned slot)	{ m_Slot = slot; }
	public:
		virtual void Bind() = 0;
	};
}