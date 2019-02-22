#include "ModelComponent.h"

namespace RA_FRAMEWORK
{

	ModelComponent::ModelComponent(const std::string& id, Mesh* mesh, Material* material):
		Component(id,ComponentType::MODEL_COMPONENT),
		p_Mesh(mesh),
		p_Material(material)
	{}

	Mesh * ModelComponent::GetMesh()
	{
		return p_Mesh;
	}

	Material * ModelComponent::GetMaterial()
	{
		return p_Material;
	}

	ModelComponent::~ModelComponent()
	{
		std::cout << "Model destructor" << std::endl;
	}
}