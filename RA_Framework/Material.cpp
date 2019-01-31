#include "Material.h"

namespace RA_FRAMEWORK
{

	Material::Material(MaterialType type):m_MaterialType(type)
	{
	}


	const MaterialType & Material::Type()
	{
		return m_MaterialType;
	}

	Material::~Material()
	{
	}
}