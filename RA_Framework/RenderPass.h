#pragma once
#include "RAUtils.h"
#include "RenderTarget.h"
namespace RA_FRAMEWORK
{
	class RARenderPass
	{
	private:
		RENDER_MASK m_Mask;
		RenderTarget* p_RenderTarget;
		int m_PassID;
		ClearMode m_ClearMode; 
		ColorRGB m_ClearColor;
		bool m_ClearDepthFlag;
	public:
		RARenderPass() = default;
		RARenderPass(RenderTarget* target, int id);												
		RARenderPass(const RARenderPass&)					= delete;
		RARenderPass& operator=(const RARenderPass&)		= delete;
		virtual ~RARenderPass();
	public:
		inline RENDER_MASK			GetMask()const								{ return m_Mask; }
		inline RenderTarget*		GetRenderTarget()							{ return p_RenderTarget; }	
		inline ClearMode			GetClearMode()const							{ return m_ClearMode; }
		inline const ColorRGB&		GetClearColor()const						{ return m_ClearColor; }
		inline bool					GetClearDepthFlag()const					{ return m_ClearDepthFlag; }
		inline void					SetClearMode(ClearMode mode)				{ m_ClearMode = mode; }
		inline void					SetClearColor(const ColorRGB& color)		{ m_ClearColor = color; }
		inline void					SetClearDepthFlag(bool clearDepth)			{ m_ClearDepthFlag = clearDepth; }
		inline void					SetRenderTarget(RenderTarget* target)		{ p_RenderTarget = target; }
		inline void					AddMaskElements(RENDER_MASK elements)		{ m_Mask |= elements; }
		inline void					RemoveMaskElements(RENDER_MASK elements)	{ m_Mask &= (~elements); }
		inline bool					HasElement(RENDER_MASK_ELEMENT element)		{ return (bool)(m_Mask&element); }
	};
}
