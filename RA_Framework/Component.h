#pragma once
#include "RAUtils.h"

namespace RA_FRAMEWORK
{
	enum class ComponentType
	{
		EMPTY = 0,
		MODEL_COMPONENT = 1 << 0,
		COLLIDER_COMPONENT = 1 << 1,
		BEHAVIOUR_COMPONENT = 1 << 2,
		CAMERA_COMPONENT = 1 << 3
	};
	class Entity;
	class Component
	{
	private:
		const std::string		m_ID;
		const ComponentType		m_Type;
		Entity*					m_pParent;
	public:
		Component() = default;
		Component(const Component&)						= default;
		Component& operator=(const Component&)			= default;
		Component(const std::string& ID, const ComponentType type);
		virtual ~Component();
	public:
		const std::string&		GetID()const				{ return m_ID; }
		ComponentType			GetType()const				{ return m_Type; };
		void					SetParent(Entity* parent)	{ m_pParent = parent; }
		Entity*					GetParent()const			{ return m_pParent; }
	};
	using ComponentUnique = std::unique_ptr<Component>;
}