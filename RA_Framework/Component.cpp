
#include "Component.h"
namespace RA_FRAMEWORK
{

	Component::Component(const std::string& ID, const ComponentType type) :
		m_ID{ ID },
		m_Type{ type }
	{

	}

	Component::~Component()
	{
		//test
	}

}