#include "GLBuiltInShaders.h"

namespace RA_FRAMEWORK
{
	GLShader* GLBuiltInShaders::VERTEX_PASSTROUGH;
	GLShader* GLBuiltInShaders::VERTEX_SKYBOX;
	GLShader* GLBuiltInShaders::FRAGMENT_TEXTURE;
	GLShader* GLBuiltInShaders::FRAGMENT_TEXTURE_ALPHA;
	GLShader* GLBuiltInShaders::FRAGMENT_TEXTURE_TINT_AND_ALPHA;
	GLShader* GLBuiltInShaders::FRAGMENT_DIRECTED_GRADIENT_COLOR;
	GLShader* GLBuiltInShaders::FRAGMENT_DIRECTED_GRADIENT_TEXTURE_AND_COLOR;
	GLShader* GLBuiltInShaders::FRAGMENT_SKYBOX;

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



		//VERTEX SKYBOX
		shaderString = "#version 330 core\n";
		shaderString += "layout(location = 0) in vec3 vertex_position;\n";
		shaderString += "out vec3 oTextcoords;\n";
		shaderString += "uniform mat4 ViewPorojection;\n";
		shaderString += "void main() { oTextcoords = vertex_position; gl_Position = vec4(vertex_position, 1.0) * ViewPorojection;}";
		VERTEX_SKYBOX = new GLShader(ShaderType::VERTEX);
		VERTEX_SKYBOX->LoadFromString(shaderString);
		compileOK = VERTEX_SKYBOX->Compile(status);
		std::cout << "Compile VERTEX SKYBOX Shader: " << compileOK;
		std::cout << "  Status: " << status << std::endl;
		if (!compileOK)
		{
			delete VERTEX_SKYBOX;
			VERTEX_SKYBOX = nullptr;
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
		compileOK = FRAGMENT_TEXTURE_TINT_AND_ALPHA->Compile(status);
		std::cout << "Compile FRAGMENT_TEXTURE_TINT_AND_ALPHA Shader: " << compileOK;
		std::cout << "  Status: " << status << std::endl;
		if (!compileOK)
		{
			delete FRAGMENT_TEXTURE_TINT_AND_ALPHA;
			FRAGMENT_TEXTURE_TINT_AND_ALPHA = nullptr;
			compileOK = true;
			status = "";
		}


		//FRAGMENT_DIRECTED_GRADIENT_TEXTURE_AND_COLOR
		shaderString = "#version 330\n in vec2 oUVs;\n uniform sampler2D _sourceTex1;\n";
		shaderString += "uniform sampler2D _sourceTex2;\n";
		shaderString += "uniform vec4 _col1;\n";
		shaderString += "uniform vec4 _col2;\n";
		shaderString += "uniform vec2 _dir;\n";
		shaderString += "uniform float _exp;\n";
		shaderString += "out vec4 colorOut;\n";
		shaderString += "void main() { vec4 col1 = texture(_sourceTex1,oUVs)*_col1;\n";
		shaderString += "vec4 col2 = texture(_sourceTex2,oUVs)*_col2;\n";
		shaderString += "float pos = float(sign(_dir.y) == 1.0);\n";
		shaderString += "float neg = 1.0 - pos;\n";
		shaderString += "vec2 uv = oUVs;";
		shaderString += "uv.y = (1.0-uv.y)*neg + uv.y*pos;\n";
		shaderString += "pos = float(sign(_dir.x) == 1.0);\n";
		shaderString += "neg = 1.0 - pos;\n";
		shaderString += "uv.x = (1.0-uv.x)*neg + uv.x*pos;\n";
		shaderString += "colorOut= mix(col1,col2, pow(length(uv*_dir),_exp));";
		shaderString += "";
		shaderString += "}\n";

		FRAGMENT_DIRECTED_GRADIENT_TEXTURE_AND_COLOR = new GLShader(ShaderType::FRAGMENT);
		FRAGMENT_DIRECTED_GRADIENT_TEXTURE_AND_COLOR->LoadFromString(shaderString);
		compileOK = FRAGMENT_DIRECTED_GRADIENT_TEXTURE_AND_COLOR->Compile(status);
		std::cout << "Compile FRAGMENT_DIRECTED_GRADIENT_TEXTURE_AND_COLOR Shader: " << compileOK;
		std::cout << "  Status: " << status << std::endl;
		if (!compileOK)
		{
			delete FRAGMENT_DIRECTED_GRADIENT_TEXTURE_AND_COLOR;
			FRAGMENT_DIRECTED_GRADIENT_TEXTURE_AND_COLOR = nullptr;
			compileOK = true;
			status = "";
		}


		//FRAGMENT_DIRECTED_GRADIENT_COLOR
		shaderString = "#version 330\n in vec2 oUVs;\n\n";
		shaderString += "uniform vec4 _col1;\n";
		shaderString += "uniform vec4 _col2;\n";
		shaderString += "uniform vec2 _dir;\n";
		shaderString += "uniform float _exp;\n";
		shaderString += "out vec4 colorOut;\n";
		shaderString += "void main() {\n";
		shaderString += "float pos = float(sign(_dir.y) == 1.0);\n";
		shaderString += "float neg = 1.0 - pos;\n";
		shaderString += "vec2 uv = oUVs;";
		shaderString += "uv.y = (1.0-uv.y)*neg + uv.y*pos;\n";
		shaderString += "pos = float(sign(_dir.x) == 1.0);\n";
		shaderString += "neg = 1.0 - pos;\n";
		shaderString += "uv.x = (1.0-uv.x)*neg + uv.x*pos;\n";
		shaderString += "colorOut= mix(_col1,_col2, pow(length(uv*_dir),_exp)); ";
		shaderString += "";
		shaderString += "}\n";


		FRAGMENT_DIRECTED_GRADIENT_COLOR = new GLShader(ShaderType::FRAGMENT);
		FRAGMENT_DIRECTED_GRADIENT_COLOR->LoadFromString(shaderString);
		compileOK = FRAGMENT_DIRECTED_GRADIENT_COLOR->Compile(status);
		std::cout << "Compile FRAGMENT_DIRECTED_GRADIENT_COLOR Shader: " << compileOK;
		std::cout << "  Status: " << status << std::endl;
		if (!compileOK)
		{
			delete FRAGMENT_DIRECTED_GRADIENT_COLOR;
			FRAGMENT_DIRECTED_GRADIENT_COLOR = nullptr;
			compileOK = true;
			status = "";
		}


		//FRAGMENT SKYBOX
		shaderString = "#version 330 core\n in vec3 oTextcoords;\n uniform sampler3D _sourceTex;\n";
		shaderString += "out vec4 colorOut;\n";
		shaderString += "void main() { colorOut = texture(_sourceTex,oTextcoords);}\n";

		FRAGMENT_SKYBOX = new GLShader(ShaderType::FRAGMENT);
		FRAGMENT_SKYBOX->LoadFromString(shaderString);
		compileOK = FRAGMENT_SKYBOX->Compile(status);
		std::cout << "Compile FRAGMENT_SKYBOX Shader: " << compileOK;
		std::cout << "  Status: " << status << std::endl;
		if (!compileOK)
		{
			delete FRAGMENT_SKYBOX;
			FRAGMENT_SKYBOX = nullptr;
			compileOK = true;
			status = "";
		}

	}

	void GLBuiltInShaders::FreeShaders()
	{
		delete VERTEX_PASSTROUGH;
		VERTEX_PASSTROUGH = nullptr;
		delete VERTEX_SKYBOX;
		VERTEX_SKYBOX = nullptr;
		delete FRAGMENT_TEXTURE;
		FRAGMENT_TEXTURE = nullptr;
		delete FRAGMENT_TEXTURE_ALPHA;
		FRAGMENT_TEXTURE_ALPHA = nullptr;
		delete FRAGMENT_TEXTURE_TINT_AND_ALPHA;
		FRAGMENT_TEXTURE_TINT_AND_ALPHA = nullptr;
		delete FRAGMENT_DIRECTED_GRADIENT_TEXTURE_AND_COLOR;
		FRAGMENT_DIRECTED_GRADIENT_TEXTURE_AND_COLOR = nullptr;
		delete FRAGMENT_DIRECTED_GRADIENT_COLOR;
		FRAGMENT_DIRECTED_GRADIENT_COLOR = nullptr;
		delete FRAGMENT_SKYBOX;
		FRAGMENT_SKYBOX = nullptr;

	}

	GLBuiltInShaders::~GLBuiltInShaders()
	{
	}
}