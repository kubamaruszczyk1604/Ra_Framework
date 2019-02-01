#pragma once

#include "RAUtils.h"
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
		GLRenderTarget(GLTexture* destination, bool depthOn);
		void Bind();
		~GLRenderTarget();
	};

}