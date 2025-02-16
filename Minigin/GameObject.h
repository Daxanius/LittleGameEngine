#pragma once
#include <memory>
#include <unordered_map>
#include <typeindex>

namespace dae
{
	class Component;

	class GameObject final 
	{
	public:
		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		virtual void FixedUpdate();
		virtual void Update(float deltaTime);
		virtual void Render() const;

		// The component returned is owned by the GameObject, there is no need to free the pointer.
		// However, you do have to check if the component has been removed in PostUpdate
		// to make sure that the pointer is still valid.
		template<typename ComponentType>
		[[nodiscard]] ComponentType* GetComponent() const {
			auto it{ m_Components.find(std::type_index(typeid(ComponentType))) };
			return (it != m_Components.end()) ? static_cast<ComponentType*>(it->second.get()) : nullptr;
		}

		// Takes ownership of the component
		template<typename ComponentType>
		void AddComponent(std::unique_ptr<ComponentType> component) {
			const auto id{ std::type_index(typeid(ComponentType)) };
			m_Components[id] = std::move(component);
			m_Components[id]->Ready(this);
		}

		// Removes a component by the next frame
		template<typename ComponentType>
		void RemoveComponent() {
			const auto id{ std::type_index(typeid(ComponentType)) };
			m_ComponentsToBeRemoved.push_back(id);
		}

		// WAWAHAWHAWHA, just for the requirement and a clean PostUpdate I guess
		template<typename ComponentType>
		[[nodiscard]] bool HasComponent() const {
			auto it{ m_Components.find(std::type_index(typeid(ComponentType))) };
			return it != m_Components.end();
		}
	private:
		void RemoveQueuedComponents();

		// Components can be held in multiple places (though it's usually just other components)
		std::unordered_map<std::type_index, std::unique_ptr<Component>> m_Components;

		// A queue of components to be removed
		std::vector<std::type_index> m_ComponentsToBeRemoved;
	};
}
