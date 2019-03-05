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
		GLuint				m_Fbo;
		GLuint				m_DepthBuffer;
		GLTexture*			m_TargetTex;
		bool				m_DepthFlag;
		bool				m_IsScreen;
		int					m_Width;
		int					m_Height;
	public:
		static void SetScreen(int w, int h);
	public:
		GLRenderTarget(const std::vector<GLTexture*>& renderTextures, bool depthBuffer = false);
		GLRenderTarget(GLTexture* renderTexture, bool depthBuffer = false);
		GLRenderTarget(const GLRenderTarget&)				 = delete;
		GLRenderTarget& operator=(const GLRenderTarget&)	 = delete;
		virtual ~GLRenderTarget();
	public:
		void Bind() override;	
		bool IsScreen() override;
		bool IsOK() override;
	};
}