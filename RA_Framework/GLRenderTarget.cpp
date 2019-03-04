#include "GLRenderTarget.h"
namespace RA_FRAMEWORK
{
	GLenum GLRenderTarget::DrawBuffers[] = 
	{ GL_COLOR_ATTACHMENT0 ,GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2,
	 GL_COLOR_ATTACHMENT3 ,GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5,
	 GL_COLOR_ATTACHMENT6 ,GL_COLOR_ATTACHMENT7 };

	void GLRenderTarget::SetScreen(int w, int h)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, w, h);
	}

	GLRenderTarget::GLRenderTarget(const std::vector<GLTexture*>& renderTextures):
		RenderTarget(0),
		m_DepthFlag(1)
	{
		if (renderTextures.size()>0)
		{
			m_Width = renderTextures[0]->Width();
			m_Height = renderTextures[0]->Height();
			m_IsScreen = false;
			glGenFramebuffers(1, &m_Fbo);
			glBindFramebuffer(GL_FRAMEBUFFER, m_Fbo);
			if (m_DepthFlag)
			{
				///http://www.songho.ca/opengl/gl_fbo.html
				glGenRenderbuffers(1, &m_DepthBuffer);
				glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBuffer);
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_Width, m_Height);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthBuffer);
			}
			//compose list of draw buffers
			for (unsigned i = 0; i < (int)renderTextures.size(); ++i)
			{
				glFramebufferTexture(GL_FRAMEBUFFER, DrawBuffers[i],  renderTextures[i]->GetID(), 0);
				//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, renderedTexture, 0);
			}
			// Set the list of draw buffers.
			glDrawBuffers((int)renderTextures.size(), DrawBuffers); // "1" is the size of DrawBuffers
		}
	}

	GLRenderTarget::GLRenderTarget(GLTexture* renderTexture):
		GLRenderTarget(std::vector<GLTexture*>(1,renderTexture ))
	{}

	void GLRenderTarget::Bind()
	{
		//if (!m_TargetTex) return;
		glBindFramebuffer(GL_FRAMEBUFFER, m_Fbo);
		glViewport(0, 0, m_Width, m_Height);
	}

	bool GLRenderTarget::IsScreen()
	{
		return m_IsScreen;
	}

	bool GLRenderTarget::IsOK()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_Fbo);
		return (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
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