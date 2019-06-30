#include "Texture.h"
namespace RA_FRAMEWORK
{
	Texture::Texture(GfxAPI API, unsigned id, unsigned slot, int w, int h, bool depth) :
		m_API(API), m_ID(id), m_Slot{ slot }, m_IsDepth{depth},c_Width{w},c_Height{h}{}
	Texture::~Texture(){}
}