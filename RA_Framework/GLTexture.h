#pragma once
#include "RAUtils.h"
#include "TextureModes.h"

namespace RA_FRAMEWORK
{
	class GLTexture
	{
	private:
		static const GLuint s_TextureAddresModeLookupTable[5];

		GLuint m_TextureID{ 0 };
	public:
		
		GLTexture(int w, int h, TextureFormat format, void* data, TextureFilterMode minFilterMode, TextureAddressMode magFilterMode, TextureAddressMode addressMode);
		GLTexture(int w, int h, TextureFormat format, void* data);
		GLTexture(int w, int h, TextureFormat format);
		GLuint GetID() { return m_TextureID; }

		//Assigns shader's uniform to the same slot as the texture.
		void Bind(const std::string& uniformName, GLuint shaderProgID, GLuint slot = 0);

		//Assigns texture to the slot and binds it as current texture.
		void Bind(GLuint slot);

		//Binds texture as current at default slot.
		void Bind();

		void Unbind();
		~GLTexture();
	};
}
