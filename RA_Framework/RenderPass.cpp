#include "RenderPass.h"
namespace RA_FRAMEWORK
{
	RenderPass::RenderPass(RenderTarget* target):
		m_Mask{0},
		p_RenderTarget{target}{}

	RenderPass::~RenderPass(){}
}