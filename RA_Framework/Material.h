#pragma once
#include "RAUtils.h"
#include "ShaderProgram.h"
#include "Texture.h"
namespace RA_FRAMEWORK
{
	struct MaterialDesc
	{
		ShaderProgram* ShaderProg = nullptr;
		Texture* AlbedoMap = nullptr;
		Texture* SpecularMap = nullptr;
		Texture* NormalMap = nullptr;
		Vec4 Ambient = Vec4(0, 0, 0, 1);
		Vec4 Albedo = Vec4(1, 1, 1, 1);
		Vec4 Specular = Vec4(0.5, 0.5, 0.5, 1);
		float Roughness = 50.0;
		float Reflectiveness = 0.0;
	};

	class Material
	{

	private:
		ShaderProgram* p_Shader;
		Texture* p_AlbedoMap;
		Texture* p_SpecularMap;
		Texture* p_NormalMap;
		Vec4 m_Ambient;
		Vec4 m_Albedo;
		Vec4 m_Specular;
		float m_Roughness;
		float m_Reflectiveness;

	public:
		Material(ShaderProgram* shaderProg);
		Material(const MaterialDesc& desc);
		Material(const Material&) = delete;
		Material& operator=(const Material&) = delete;
		void SetAlbedoMap(Texture* texture) { p_AlbedoMap = texture; }
		void SetSpecularMap(Texture* texture) { p_SpecularMap = texture; }
		void SetNormalMap(Texture* texture) { p_NormalMap = texture; }
		void SetAmbientColor(const Vec4& color) { m_Ambient = color; }
		void SetAlbedoColor(const Vec4& color) { m_Albedo = color; }
		void SetSpecularColor(const Vec4& color) { m_Specular = color; }
		void SetRoughness(float roughness) { m_Roughness = roughness; }
		void SetReflectiveness(float reflectiveness) { m_Reflectiveness = reflectiveness; }

		bool GetAlbedoMap(Texture*& map) { map = p_AlbedoMap; return (p_AlbedoMap != nullptr); }
		bool GetSpecularMap(Texture*& map) { map = p_SpecularMap; return (p_SpecularMap != nullptr); }
		bool GetNormalMap(Texture*& map) { map = p_NormalMap; return (p_NormalMap != nullptr); }

		const Vec4& GetAmbientColor() { return m_Ambient; }
		const Vec4& GetAlbedoColor() { return m_Albedo; }
		const Vec4& GetSpecularColor() { return m_Specular; }

		float GetRoughness() { return m_Roughness; }
		float GetReflectiveness() { return m_Reflectiveness; }
		virtual ~Material();
	};

}