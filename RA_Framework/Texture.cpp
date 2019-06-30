#include "Texture.h"
namespace RA_FRAMEWORK
{
	Texture::Texture(GfxAPI API, unsigned id, unsigned slot, bool depth) :
		m_API(API), m_ID(id), m_Slot{ slot }, m_IsDepth{depth}{}
	Texture::~Texture(){}
}