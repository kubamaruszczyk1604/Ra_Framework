#include "ModelComponent.h"

namespace RA_FRAMEWORK
{

	ModelComponent::ModelComponent(const std::string& id, Mesh* mesh, Material* material):Component(id,ComponentType::MODEL_COMPONENT),m_pMesh(mesh),m_pMaterial(material)
	{

	}


	Mesh * ModelComponent::GetMesh()
	{
		return m_pMesh;
	}

	Material * ModelComponent::GetMaterial()
	{
		return m_pMaterial;
	}

	ModelComponent::~ModelComponent()
	{
	}
}