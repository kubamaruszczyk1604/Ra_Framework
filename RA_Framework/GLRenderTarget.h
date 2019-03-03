#pragma once
#include "GLTexture.h"
#include "RenderTarget.h"
namespace RA_FRAMEWORK
{
	class GLRenderTarget:public RenderTarget
	{
	private:
		GLuint m_Fbo;
		GLuint m_DepthBuffer;
		GLTexture* m_TargetTex;
		bool m_DepthFlag;
	public:
		static void SetScreen(int w, int h);
	public:
		GLRenderTarget(GLTexture* destination, int id);
		GLRenderTarget(const GLRenderTarget&) = delete;
		GLRenderTarget& operator=(const GLRenderTarget&) = delete;
		virtual ~GLRenderTarget();
	public:
		void Bind() override;	
		bool IsScreen() override;
	};
}