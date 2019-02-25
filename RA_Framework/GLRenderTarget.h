#pragma once
#include "GLTexture.h"
namespace RA_FRAMEWORK
{
	class GLRenderTarget
	{
	private:
		GLuint m_Fbo;
		GLuint m_DepthBuffer;
		GLTexture* m_TargetTex;
		bool m_DepthFlag;
	public:
		static void SetScreen(int w, int h);
	public:
		explicit GLRenderTarget(GLTexture* destination, bool depthOn);
		GLRenderTarget(const GLRenderTarget&) = delete;
		GLRenderTarget& operator=(const GLRenderTarget&) = delete;
		~GLRenderTarget();
	public:
		void Bind();	
	};
}