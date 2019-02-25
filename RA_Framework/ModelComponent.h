#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Material.h"
namespace RA_FRAMEWORK
{
	class ModelComponent : public Component
	{
	public:
		Mesh* p_Mesh;
		Material* p_Material;
	public:
		ModelComponent(const std::string& id, Mesh* mesh, Material* material);
		ModelComponent operator=(const ModelComponent&) = delete;
		ModelComponent(const ModelComponent&) = delete;
		ModelComponent() = delete;
	public:
		Mesh* GetMesh();
		Material* GetMaterial();
	public:
		virtual ~ModelComponent();
	};
}