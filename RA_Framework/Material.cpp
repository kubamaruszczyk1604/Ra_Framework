#include "Material.h"

namespace RA_FRAMEWORK
{

	Material::Material(ShaderProgram* shaderProg):
		p_Shader(shaderProg),
		p_NormalMap(nullptr), p_AlbedoMap(nullptr), p_SpecularMap(nullptr),
		m_Ambient(Vec4(0,0,0,1)), m_Albedo(Vec4(1)),m_Specular(Vec4(0.5,0.5,0.5,1)),
		m_Roughness(50), m_Reflectiveness(0)

	{
	}

	Material::Material(const MaterialDesc& desc)
	{
		p_Shader = desc.ShaderProg;
		p_NormalMap = desc.NormalMap;
		p_AlbedoMap = desc.AlbedoMap;
		p_SpecularMap = desc.SpecularMap;
		m_Ambient = desc.Ambient;
		m_Albedo = desc.Albedo;
		m_Specular = desc.Specular;
		m_Roughness = desc.Roughness;
		m_Reflectiveness = desc.Reflectiveness;
	}

	Material::~Material()
	{
	}
}