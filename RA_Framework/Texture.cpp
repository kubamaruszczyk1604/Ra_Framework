#include "Texture.h"
namespace RA_FRAMEWORK
{
	Texture::Texture(GfxAPI API, unsigned id, unsigned slot) :m_API(API), m_ID(id), m_Slot{slot}{}
	Texture::~Texture(){}
}