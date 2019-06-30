#pragma once
#include "RATypes.h"
#include"TextureModes.h"
namespace RA_FRAMEWORK
{
	struct TextureFormatDescriptor
	{
		TextureWrapMode			WRAP_MODE				{ TextureWrapMode::WRAP };
		TextureFilterMode		MIN_FILTER_MODE			{ TextureFilterMode::BILINEAR };
		TextureFilterMode		MAG_FILTER_MODE			{ TextureFilterMode::BILINEAR };
		InputPixelDataType		INPUT_DATA_TYPE			{ InputPixelDataType::UNISGNED_BYTE };
		InputPixelFormat		INPUT_PIXEL_FORMAT		{ InputPixelFormat::RGBA };
		TextureDataFormat		TEXTURE_DATA_FORMAT		{ TextureDataFormat::RGBA };
		bool					GEN_MIPMAPS				{ false };
	};

	class Texture
	{
	private:
		const GfxAPI m_API;
	protected:
		Texture(GfxAPI API, unsigned id, unsigned slot, bool depth = false);
		unsigned					m_ID;
		unsigned					m_Slot;
		bool						m_IsDepth;
		TextureFormatDescriptor		m_TextureDescriptor;
	protected:
		inline void SetTextureDescriptor(const TextureFormatDescriptor& desc) { m_TextureDescriptor = desc; }
	public:
		Texture(const Texture&)					= delete;
		Texture& operator=(const Texture&)		= delete;
		virtual ~Texture();
	public:
		inline GfxAPI		GetAPI()						{ return m_API; }
		inline unsigned		GetID()const 					{ return m_ID; }
		inline unsigned		GetSlot()const					{ return m_Slot; }
		inline void			SetSlot(const unsigned slot)	{ m_Slot = slot; }
		inline bool			IsDepthTexture()				{ return m_IsDepth; }
	public:
		inline TextureFormatDescriptor GetDescriptor() { return m_TextureDescriptor; }
	public:
		virtual void		Bind() = 0;
		virtual void		Unbind() = 0;
		virtual void		GenerateMipmaps() = 0;
		virtual void		SetWrapMode(TextureWrapMode mode) = 0;
		virtual void		SetMinFilterMode(TextureFilterMode filterMode) = 0;
		virtual void		SetMagFilterMode(TextureFilterMode filterMode) = 0;
		virtual void		SetFilterMode(TextureFilterMode minMode, TextureFilterMode magMode) = 0;
	};

}