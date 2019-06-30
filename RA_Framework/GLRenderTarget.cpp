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

	GLRenderTarget::GLRenderTarget(const std::vector<GLTexture*>& renderTextures, DeptAttachmentType depthAttachmentType, bool genPosprocessTexture):
		RenderTarget(0, genPosprocessTexture),
		m_DepthAttachmentType{depthAttachmentType},
		m_pColorAttachments{renderTextures}
	{
		if (renderTextures.size()>0)
		{
			m_Width = renderTextures[0]->Width();
			m_Height = renderTextures[0]->Height();
			m_IsScreen = false;
			glGenFramebuffers(1, &m_Fbo);
			glBindFramebuffer(GL_FRAMEBUFFER, m_Fbo);

			//compose list of draw buffers
			for (unsigned i = 0; i < (int)renderTextures.size(); ++i)
			{
				glFramebufferTexture(GL_FRAMEBUFFER, DrawBuffers[i],  renderTextures[i]->GetID(), 0);
				//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, renderedTexture, 0);
			}
			// Set the list of draw buffers.
			glDrawBuffers((int)renderTextures.size(), DrawBuffers); 

			if (m_DepthAttachmentType == DeptAttachmentType::RENDER_BUFFER)
			{
				///http://www.songho.ca/opengl/gl_fbo.html
				glGenRenderbuffers(1, &m_DepthBuffer);
				glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBuffer);
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_Width, m_Height);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthBuffer);
			}
			else if (m_DepthAttachmentType == DeptAttachmentType::DEPTH_TEXTURE)
			{
				/*TextureFormatDescriptor desc;
				desc.INPUT_PIXEL_FORMAT = InputPixelFormat::DEPTH_COMPONENT;
				desc.TEXTURE_DATA_FORMAT = TextureDataFormat::DEPTH_COMPONENT;
				desc.INPUT_DATA_TYPE = InputPixelDataType::FLOAT;
				desc.WRAP_MODE = TextureWrapMode::CLAMP;
				desc.MIN_FILTER_MODE = TextureFilterMode::NEAREST;
				desc.MAG_FILTER_MODE = TextureFilterMode::NEAREST;
				m_pDepthTexture = new GLTexture(m_Width, m_Height, desc);
				m_pDepthTexture->Bind();*/
				m_pDepthTexture = GLTexture::GenerateDepthTexture(m_Width, m_Height);
				glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_pDepthTexture->GetID(), 0);

			}

			if(m_HasPostprocessTexture)
			m_PostprocessTexture = new GLTexture(m_Width, m_Height, renderTextures[0]->GetDescriptor());
		}
	}

	GLRenderTarget::GLRenderTarget(GLTexture* renderTexture, DeptAttachmentType depthAttachmentType, bool genPosprocessTexture):
		GLRenderTarget(std::vector<GLTexture*>(1,renderTexture ), depthAttachmentType, genPosprocessTexture) {}

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

	Texture* GLRenderTarget::GetColorAttachment(unsigned index)
	{
		if(m_pColorAttachments.size()==0) return nullptr;
		if (m_pColorAttachments.size() >= index) return nullptr;
		return m_pColorAttachments[index];
	}

	Texture * GLRenderTarget::GetPostProcessTexture()
	{
		return m_HasPostprocessTexture ? m_PostprocessTexture : nullptr;
	}

	Texture* GLRenderTarget::GetDepthTexture()
	{
		return m_pDepthTexture;
	}

	GLRenderTarget::~GLRenderTarget()
	{
		if (m_HasPostprocessTexture) 
			delete m_PostprocessTexture;
		if (m_DepthAttachmentType == DeptAttachmentType::RENDER_BUFFER)
		{
			glDeleteRenderbuffers(1, &m_DepthBuffer);
		}
		else if (m_DepthAttachmentType == DeptAttachmentType::DEPTH_TEXTURE)
		{
			delete m_pDepthTexture;
		}
		glDeleteFramebuffers(1, &m_Fbo);
	}
}