#pragma once
#include "RAUtils.h"
namespace RA_FRAMEWORK
{
	enum class MaterialType
	{
		PHONG = 0,
		COOK_TORRANCE = 1 << 0
	};

	class Material
	{

	private:
		MaterialType m_MaterialType;
	public:
		Material(MaterialType type);
		Material(const Material&) = delete;
		Material& operator=(const Material&) = delete;
		const MaterialType& Type();
		virtual ~Material();
	};

}