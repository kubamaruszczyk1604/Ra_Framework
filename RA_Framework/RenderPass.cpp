#include "RenderPass.h"
namespace RA_FRAMEWORK
{
	RenderPass::RenderPass(RenderTarget* target, int id, RENDER_MASK mask):
		m_Mask{mask},
		m_PassID{id},
		p_RenderTarget{target}{}

	RenderPass::~RenderPass(){}
}