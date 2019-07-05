#pragma once
#include "GLShaderProgram.h"
namespace  RA_FRAMEWORK
{
	class GLBuiltInShaders
	{
	public:
		GLBuiltInShaders() = delete;
		GLBuiltInShaders(const GLBuiltInShaders&) = delete;
		GLBuiltInShaders& operator=(const GLBuiltInShaders&) = delete;
		static GLShader* VERTEX_PASSTROUGH;
		static GLShader* FRAGMENT_TEXTURE;
		static GLShader* FRAGMENT_TEXTURE_ALPHA;
		static GLShader* FRAGMENT_TEXTURE_TINT_AND_ALPHA;
		static void Initiate();
		static void FreeShaders();
		~GLBuiltInShaders();
	};

}