#include "RenderPass.h"
namespace RA_FRAMEWORK
{

	RARenderPass::RARenderPass(RenderTarget* target, int id):
		m_Mask{RENDER_MASK_ELEMENT::RENDERABLE},
		m_PassID{id},
		p_RenderTarget{target},
		m_ClearMode{ClearMode::COLOR},
		m_ClearColor{ColorRGB(0,0,0)},
		m_ClearDepthFlag{true} {}

	RARenderPass::~RARenderPass(){}
}