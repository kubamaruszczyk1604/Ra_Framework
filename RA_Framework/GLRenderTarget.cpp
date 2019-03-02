#include "GLRenderTarget.h"
namespace RA_FRAMEWORK
{
	void GLRenderTarget::SetScreen(int w, int h)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, w, h);
	}

	GLRenderTarget::GLRenderTarget(GLTexture* destination, int id):
		RenderTarget(id),
		m_TargetTex(destination),
		m_DepthFlag(0)
	{
		glGenFramebuffers(1, &m_Fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, m_Fbo);
	/*	if (m_DepthFlag)
		{
			///http://www.songho.ca/opengl/gl_fbo.html
			glGenRenderbuffers(1, &m_DepthBuffer);
			glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBuffer);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, destination->Width(), destination->Height());
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthBuffer);
		}*/
		// Set m_TargetTex as colour attachement #0
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_TargetTex->GetID(), 0);
		// Set the list of draw buffers.
		GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
	}

	void GLRenderTarget::Bind()
	{
		//m_TargetTex->Bind();
		glBindFramebuffer(GL_FRAMEBUFFER, m_Fbo);
		glViewport(0, 0, m_TargetTex->Width(), m_TargetTex->Height());
	}

	GLRenderTarget::~GLRenderTarget()
	{
		if (m_DepthFlag)
		{
			glDeleteRenderbuffers(1, &m_DepthBuffer);
		}
		glDeleteFramebuffers(1, &m_Fbo);
	}
}