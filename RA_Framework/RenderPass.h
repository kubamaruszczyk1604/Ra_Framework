#pragma once
#include "RAUtils.h"
#include "RenderTarget.h"
namespace RA_FRAMEWORK
{
	class RenderPass
	{
	private:
		RENDER_MASK m_Mask;
		RenderTarget* p_RenderTarget;
		int m_PassID;
		ClearMode m_ClearMode;
		ColorRGB m_ClearColor;

	public:
		RenderPass(RenderTarget* target, int id, RENDER_MASK mask);
		RenderPass(const RenderPass&) = delete;
		RenderPass& operator=(const RenderPass&) = delete;
		virtual ~RenderPass();
	public:
		inline RENDER_MASK			GetMask()const								{ return m_Mask; }
		inline RenderTarget*		GetRenderTarget()const						{ return p_RenderTarget; }	
		inline void					SetRenderTarget(RenderTarget* target)		{ p_RenderTarget = target; }
		inline void					AddMaskElements(RENDER_MASK elements)		{ m_Mask |= elements; }
		inline void					RemoveMaskElements(RENDER_MASK elements)	{ m_Mask &= (~elements); }
		inline bool					HasElement(RENDER_MASK_ELEMENT element)		{ return (bool)(m_Mask&element); }
	};
}
