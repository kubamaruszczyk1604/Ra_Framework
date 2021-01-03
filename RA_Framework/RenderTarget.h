#pragma once
#include"Texture.h"
namespace RA_FRAMEWORK
{
	class RenderTarget
	{
	protected:
		int m_ID;
		bool m_HasPostprocessTexture;
	protected:
		RenderTarget(int id, bool hasPostTexture = false) : m_ID{ id }, m_HasPostprocessTexture{hasPostTexture}{}
	public:
		RenderTarget(const RenderTarget&) = delete;
		RenderTarget& operator=(const RenderTarget&) = delete;
		virtual ~RenderTarget() {}
	public:
		int				GetID()const				{ return m_ID; }
		bool			HasPostprocessTexture()		{ return m_HasPostprocessTexture; }
	public:
		virtual void		Bind() = 0;
		virtual bool		IsScreen() = 0;
		virtual bool		IsOK() = 0;
		virtual Texture*	GetDepthTexture() = 0;
		virtual Texture*	GetColorAttachment(unsigned index) = 0;
		virtual Texture*	GetPostProcessTexture() = 0;
	};
}