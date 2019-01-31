#pragma once

#include "RAUtils.h"
#include "GLTexture.h"

namespace RA_FRAMEWORK
{

	class RenderTarget
	{
	private:
		GLuint m_Fbo;
	public:
		static void SetDefault();
		RenderTarget();
		~RenderTarget();
	};

}