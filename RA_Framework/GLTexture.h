#pragma once
#include "RAUtils.h"
#include "TextureModes.h"
#include "Texture.h"
#include "GLTypeLUTs.h"
#include "ImageLoader.h"
namespace RA_FRAMEWORK
{
	class GLTexture: public Texture
	{
	private:
		const int c_Width;
		const int c_Height;
	public:
		GLTexture(int w, int h, const TextureFormatDescriptor& desc, void* data);
		GLTexture(int w, int h, const TextureFormatDescriptor& desc);
		GLTexture(InputPixelDataType inputPixelFormat, TextureDataFormat internalFormat, Image& image);
		GLTexture(TextureDataFormat internalFormat, Image& image);
		GLTexture(Image& image);
		~GLTexture();
	public:
		//Assigns shader's uniform to the same slot as the texture.
		void		Bind(const String& uniformName, uint shaderProgID);
		//Assigns texture to the slot and binds it as current texture.
		void		Bind(uint slot);
		//Binds texture as current at default slot.
		void			Bind()override;
		void			Unbind()override;
		void			GenerateMipmaps()override;
		void			SetWrapMode(TextureWrapMode mode);
		void			SetMinFilterMode(TextureFilterMode filterMode);
		void			SetMagFilterMode(TextureFilterMode filterMode);
		void			SetFilterMode(TextureFilterMode minMode, TextureFilterMode magMode);
		unsigned		GetMipmapLevel();
	public:
		int				Width()		{ return c_Width; }
		int				Height()	{ return c_Height; }
		uint			GetID()		{ return m_ID; }
	};
}
