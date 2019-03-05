#pragma once
#include "GLTexture.h"
#include "RenderTarget.h"
namespace RA_FRAMEWORK
{
	class GLRenderTarget:public RenderTarget
	{
	private:
		static GLenum		DrawBuffers[];
	private:
		GLuint						m_Fbo;
		GLuint						m_DepthBuffer;
		GLTexture*                  m_pDepthTexture;
		DeptAttachmentType			m_DepthAttachmentType;
		bool						m_IsScreen;
		int							m_Width;
		int							m_Height;
		std::vector<GLTexture*>		m_pColorAttachments;
	public:
		static void SetScreen(int w, int h);
	public:
		GLRenderTarget(const std::vector<GLTexture*>& renderTextures, DeptAttachmentType depthAttachmentType = DeptAttachmentType::NONE);
		GLRenderTarget(GLTexture* renderTexture, DeptAttachmentType depthAttachmentType = DeptAttachmentType::NONE);
		GLRenderTarget(const GLRenderTarget&)				 = delete;
		GLRenderTarget& operator=(const GLRenderTarget&)	 = delete;
		virtual ~GLRenderTarget();
	public:
		void				Bind() override;	
		bool				IsScreen() override;
		bool				IsOK() override;
		GLTexture*			GetColorAttachment(unsigned index);
		GLTexture*			GetDepthTexture();

	};
}