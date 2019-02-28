#pragma once
#include"RATypes.h"
namespace RA_FRAMEWORK
{
	namespace RA_BUILT_IN_SHADERS
	{

		
		static const String GL_Vert_MVPVeryBasic =
			"#version 330\n"
			"layout(location = 0) in vec3 vertex_position;\n"
			"layout(location = 1) in vec3 vertex_normal;\n"
			"layout(location = 2) in vec3 tangent;\n"
			"layout(location = 3) in vec2 uvs;\n\n"

			"uniform mat4 uMVP;\n"
			"uniform float uTime;\n\n"

			"//Output\n"
			"out vec2 oUVs;\n"
			"out float oTime;\n\n"

			"void main()\n"
			"{\n"
			"	 oUVs = uvs;\n"
			"	 oTime = uTime;\n"
			"	 gl_Position = uMVP * vec4(vertex_position, 1.0);\n"
			" }";
		
		static const String GL_Vert_MVPBasic =
			"#version 330\n"
			"layout(location = 0) in vec3 vertex_position;\n"
			"layout(location = 1) in vec3 vertex_normal;\n"
			"layout(location = 2) in vec3 tangent;\n"
			"layout(location = 3) in vec2 uvs;\n\n"

			"uniform mat4 uWORLD;\n"
			"uniform mat4 uMVP;\n"
			"uniform vec3 uCameraPosition;\n"
			"uniform float uTime;\n\n"

			"//Output\n"
			"out vec3 oPosition_WorldSpace;\n"
			"out vec3 oPosition_ObjectSpace;\n"
			"out vec3 oNormal_ObjectScpace;\n"
			"out vec2 oUVs;\n"
			"out vec3 oCamera_WorldSpace;\n"
			"out float oTime;\n\n"

			"void main()\n"
			"{\n"
			"	 oPosition_WorldSpace = (uWORLD * vec4(vertex_position, 1)).xyz;\n"
			"	 oPosition_ObjectSpace = vertex_position;\n"
			"	 oNormal_ObjectScpace = vertex_normal;\n\n"

			"	 oUVs = uvs;\n"
			"	 oCamera_WorldSpace = uCameraPosition;\n"
			"	 oTime = uTime;\n"

			"	 gl_Position = uMVP * vec4(vertex_position, 1.0);\n"
			" }";


		static const String GL_Vert_MVPStandard =
			"#version 330\n"
			"layout(location = 0) in vec3 vertex_position;\n"
			"layout(location = 1) in vec3 vertex_normal;\n"
			"layout(location = 2) in vec3 tangent;\n"
			"layout(location = 3) in vec2 uvs;\n\n"

			"uniform mat4 uWORLD;\n"
			"uniform mat4 uWORLD_INVERSE;\n"
			"uniform mat4 uVIEW;\n"
			"uniform mat4 uMVP;\n"
			"uniform vec3 uCameraPosition;\n"
			"uniform float uTime;\n\n"

			"//Output\n"
			"out vec3 oPosition_WorldSpace;\n"
			"out vec3 oPosition_ObjectSpace;\n"
			"out vec3 oPosition_EyeSpace;\n"
			"out vec3 oNormal_InvWorldSpace;\n"
			"out vec3 oNormal_ObjectScpace;\n"
			"out vec2 oUVs;\n"
			"out vec3 oCamera_WorldSpace;\n"
			"out float oTime;\n\n"

			"void main()\n"
			"{\n"
			"	 oPosition_WorldSpace = (uWORLD * vec4(vertex_position, 1)).xyz;\n"
			"	 oPosition_ObjectSpace = vertex_position;\n"
			"	 oPosition_EyeSpace = (uVIEW*vec4(vertex_position, 1.0)).xyz;\n\n"

			"	 oNormal_InvWorldSpace = mat3(uWORLD_INVERSE) * vertex_normal;\n"
			"	 oNormal_ObjectScpace = vertex_normal;\n\n"

			"	 oUVs = uvs;\n"
			"	 oCamera_WorldSpace = uCameraPosition;\n"
			"	 oTime = uTime;\n"

			"	 gl_Position = uMVP * vec4(vertex_position, 1.0);\n"
			" }";
	}
	

}