#include "GLBuiltInShaders.h"

namespace RA_FRAMEWORK
{
	GLShader* GLBuiltInShaders::VERTEX_PASSTROUGH;
	GLShader* GLBuiltInShaders::FRAGMENT_TEXTURE;
	GLShader* GLBuiltInShaders::FRAGMENT_TEXTURE_ALPHA;
	GLShader* GLBuiltInShaders::FRAGMENT_TEXTURE_TINT_AND_ALPHA;

	void RA_FRAMEWORK::GLBuiltInShaders::Initiate()
	{

		//VERTEX
		String shaderString = "#version 330\n";
		shaderString += "layout(location = 0) in vec3 vertex_position;\n";
		shaderString += "layout(location = 1) in vec3 vertex_normal;\n";
		shaderString += "layout(location = 2) in vec3 tangent;\n";
		shaderString += "layout(location = 3) in vec2 uvs;\n";
		shaderString += "out vec2 oUVs;\n";
		shaderString += "void main() { oUVs = uvs; gl_Position = vec4(vertex_position, 1.0);}";

		std::string status;
		std::cout << "\nCOMPILING BUILT-IN GL SHADERS:" << std::endl;
		VERTEX_PASSTROUGH = new GLShader(ShaderType::VERTEX);
		VERTEX_PASSTROUGH->LoadFromString(shaderString);
		bool compileOK = VERTEX_PASSTROUGH->Compile(status);
		std::cout << "Compile VERTEX_PASSTROUGH Shader: " << compileOK;
		std::cout << "  Status: " << status << std::endl;
		if (!compileOK)
		{
			delete VERTEX_PASSTROUGH;
			VERTEX_PASSTROUGH = nullptr;
			compileOK = true;
			status = "";
		}


		//FRAGMENT TEXTURE
		shaderString = "#version 330\n in vec2 oUVs;\n uniform sampler2D _sourceTex;\n";
		shaderString += "out vec4 colorOut;\n";
		shaderString += "void main() { colorOut = texture(_sourceTex,oUVs);}\n";

		FRAGMENT_TEXTURE = new GLShader(ShaderType::FRAGMENT);
		FRAGMENT_TEXTURE->LoadFromString(shaderString);
		compileOK= FRAGMENT_TEXTURE->Compile(status);
		std::cout << "Compile FRAGMENT_TEXTURE Shader: " << compileOK;
		std::cout << "  Status: " << status << std::endl;
		if (!compileOK)
		{ 
			delete FRAGMENT_TEXTURE;
			FRAGMENT_TEXTURE = nullptr;
			compileOK = true;
			status = "";
		}

		//FRAGMENT TEXTURE ALPHA
		shaderString = "#version 330\n in vec2 oUVs;\n uniform sampler2D _sourceTex;\n";
		shaderString += "out vec4 colorOut;\n";
		shaderString += "uniform float _alpha;\n";
		shaderString += "void main() { colorOut = texture(_sourceTex,oUVs)*vec4(1.0,1.0,1.0,_alpha);}\n";
		
		FRAGMENT_TEXTURE_ALPHA = new GLShader(ShaderType::FRAGMENT);
		FRAGMENT_TEXTURE_ALPHA->LoadFromString(shaderString);
		compileOK = FRAGMENT_TEXTURE_ALPHA->Compile(status);
		std::cout << "Compile FRAGMENT_TEXTURE_ALPHA Shader: " << compileOK;
		std::cout << "  Status: " << status << std::endl;
		if (!compileOK)
		{
			delete FRAGMENT_TEXTURE_ALPHA;
			FRAGMENT_TEXTURE_ALPHA = nullptr;
			compileOK = true;
			status = "";
		}

		//FRAGMENT TEXTURE TINT AND ALPHA
		shaderString = "#version 330\n in vec2 oUVs;\n uniform sampler2D _sourceTex;\n";
		shaderString += "out vec4 colorOut;\n";
		shaderString += "uniform vec3 _tint;\n";
		shaderString += "uniform float _alpha;\n";
		shaderString += "void main() { colorOut = texture(_sourceTex,oUVs)*vec4(_tint.x,_tint.y,_tint.z,_alpha);}\n";

		FRAGMENT_TEXTURE_TINT_AND_ALPHA = new GLShader(ShaderType::FRAGMENT);
		FRAGMENT_TEXTURE_TINT_AND_ALPHA->LoadFromString(shaderString);
		bool fragOK = FRAGMENT_TEXTURE_TINT_AND_ALPHA->Compile(status);
		std::cout << "Compile FRAGMENT_TEXTURE_TINT_AND_ALPHA Shader: " << fragOK;
		std::cout << "  Status: " << status << std::endl;
		if (!compileOK)
		{
			delete FRAGMENT_TEXTURE_TINT_AND_ALPHA;
			FRAGMENT_TEXTURE_TINT_AND_ALPHA = nullptr;
			compileOK = true;
			status = "";
		}
	}

	void GLBuiltInShaders::FreeShaders()
	{
		delete VERTEX_PASSTROUGH;
		delete FRAGMENT_TEXTURE;
		delete FRAGMENT_TEXTURE_ALPHA;
		delete FRAGMENT_TEXTURE_TINT_AND_ALPHA;
	}

	GLBuiltInShaders::~GLBuiltInShaders()
	{
	}
}