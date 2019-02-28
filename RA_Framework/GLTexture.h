#pragma once
#include "RAUtils.h"
#include "TextureModes.h"
#include "Texture.h"
#include "GLTypeLUTs.h"
namespace RA_FRAMEWORK
{
	class GLTexture: public Texture
	{
	private:
		const int c_Width;
		const int c_Height;
	public:
		GLTexture(int w, int h, TextureFormat format, void* data, TextureFilterMode minFilterMode, TextureAddressMode magFilterMode, TextureAddressMode addressMode);
		GLTexture(int w, int h, TextureFormat format, void* data);
		GLTexture(int w, int h, TextureFormat format);
		~GLTexture();
	public:
		//Assigns shader's uniform to the same slot as the texture.
		void		Bind(const String& uniformName, uint shaderProgID, uint slot = 0);
		//Assigns texture to the slot and binds it as current texture.
		void		Bind(uint slot);
		//Binds texture as current at default slot.
		void		Bind()override;
		void		Unbind();
	public:
		int			Width()		{ return c_Width; }
		int			Height()	{ return c_Height; }
		uint		GetID()		{ return m_ID; }
	};
}
