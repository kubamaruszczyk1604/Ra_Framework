#include "RenderTarget.h"


namespace RA_FRAMEWORK
{
	void RenderTarget::SetDefault()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	RenderTarget::RenderTarget()
	{
		glGenFramebuffers(1, &m_Fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, m_Fbo);
	}


	RenderTarget::~RenderTarget()
	{
		glDeleteFramebuffers(1, &m_Fbo);
	}
}