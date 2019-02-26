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
		explicit GLRenderTarget(GLTexture* destination);
		GLRenderTarget(const GLRenderTarget&) = delete;
		GLRenderTarget& operator=(const GLRenderTarget&) = delete;
		~GLRenderTarget();
	public:
		void Bind();	
	};
}