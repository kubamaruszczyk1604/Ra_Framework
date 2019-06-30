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
		int			m_ErrorCode = 0; // 0 - no errors, 1 - binding error (uniform not found in shader)
	private:
		GLTexture(int w, int h); //generate depth texture
	public:
		static GLTexture* GenerateDepthTexture(int w, int h);
	public:
		GLTexture(int w, int h, const TextureFormatDescriptor& desc, void* data);
		GLTexture(int w, int h, const TextureFormatDescriptor& desc);
		GLTexture(InputPixelDataType inputPixelFormat, TextureDataFormat internalFormat, Image& image);
		GLTexture(TextureDataFormat internalFormat, Image& image);
		GLTexture(Image& image);
		~GLTexture();
	public:
		//Assigns shader's uniform to the same slot as the texture.
		bool			Bind(const String& uniformName, uint shaderProgID);
		//Assigns texture to the slot and binds it as current texture.
		void			Bind(uint slot);
		//Binds texture as current at default slot.
		void			Bind()override;
		void			Unbind()override;
		void			GenerateMipmaps()override;
		void			SetWrapMode(TextureWrapMode mode)override;
		void			SetMinFilterMode(TextureFilterMode filterMode)override;
		void			SetMagFilterMode(TextureFilterMode filterMode)override;
		void			SetFilterMode(TextureFilterMode minMode, TextureFilterMode magMode)override;
		uint			GetMipmapLevel()override;
		
	public:
		int				GetLastErrorCode()	{ return m_ErrorCode; }
		void			ClearErrors()		{ m_ErrorCode = 0; }
	};
}
