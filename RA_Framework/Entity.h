#pragma once
#include "RAUtils.h"
#include "KLMList.h"
#include "Component.h"
#include "Transform.h"
namespace RA_FRAMEWORK
{
	class Entity
	{
	private:
		static Mat4 s_Identity;
		KLMList<Entity*> m_pChildren;
		KLMList<ComponentUnique> m_pComponents;
		Component* m_pCachedComponent_Model;
		std::string m_ID;
		Entity* m_pParent;
		Transform m_Transform;
		int m_ComponentMask;
		bool m_DeleteMeFlag{ false };
	public:
		explicit Entity() = default;
		explicit Entity(const std::string& ID);
		Entity(const Entity&) = delete;
		Entity& operator=(const Entity&) = delete;
		virtual ~Entity();		
	public:
		void AddChild(Entity* child);
		Entity* FindInChildreen(const std::string& name);
		void RemoveFromChildreen(Entity* child);
		void DeleteAllChildreen();
		void AddComponent(ComponentUnique component);
		Component* GetFirstComponentOfType(ComponentType type);
		bool TryGetCachedModel(Component*& outModel)const;
		void CalculateTransform();
		void Delete();

		bool ShouldDelete()const				 { return m_DeleteMeFlag; }
		void SetParent(Entity* const entity)	 { m_pParent = entity; }	
		Entity* GetParent() const	 			 { return m_pParent; }
		const std::string& GetName() const		 { return m_ID; }
		int GetComponentCount() const			 { return m_pComponents.Count(); }
		Component* GetComponent(int const index) { m_pComponents[index]; }
		Transform* GetTransform()     	 { return &m_Transform; }		
	};
}