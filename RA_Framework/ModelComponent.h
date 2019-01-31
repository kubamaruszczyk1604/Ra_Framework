#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Material.h"
namespace RA_FRAMEWORK
{
	class ModelComponent : public Component
	{
	public:
		Mesh* m_pMesh;
		Material* m_pMaterial;
	public:
		ModelComponent(const std::string& id, Mesh* mesh, Material* material);
		ModelComponent() = delete;
		ModelComponent operator=(const ModelComponent&) = delete;
		ModelComponent(const ModelComponent&) = delete;
		Mesh* GetMesh();
		Material* GetMaterial();
		virtual ~ModelComponent();
	};

}