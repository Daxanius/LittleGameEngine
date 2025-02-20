#pragma once
#include <memory>
#include <unordered_map>
#include <typeindex>

namespace dae
{
	class BaseComponent;

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
		// However, you do have to check if the component has been removed in PostUpdate.
		template<typename ComponentType>
		requires std::derived_from<ComponentType, BaseComponent>
		[[nodiscard]] ComponentType* GetComponent() const {
			ComponentType* resultComponent{};
			std::ignore = std::ranges::find_if(m_components, [&resultComponent](auto& basecomponent) {
				resultComponent = dynamic_cast<ComponentType*>(basecomponent.get());
				return resultComponent != nullptr;
			});

			return resultComponent;
		}

		// Creates a component, similar to std::make_unique
		template<typename ComponentType, typename... Args>
		requires std::derived_from<ComponentType, BaseComponent>
		void AddComponent(Args&&... args) {
			m_components.push_back(std::make_unique<ComponentType>(*this, std::forward<Args>(args)...));
		}

		template<typename ComponentType>
		requires std::derived_from<ComponentType, BaseComponent>
		[[nodiscard]] bool HasComponent() const {
			auto it = std::ranges::find_if(m_components, [](const auto& basecomponent) {
				return dynamic_cast<ComponentType*>(basecomponent.get()) != nullptr;
			});

			return it != m_components.end();
		}
	private:
		void RemoveDestroyedComponents();

		// GameObjects won't have that many components, thus having a single vector of BaseComponents is fine.
		std::vector<std::unique_ptr<BaseComponent>> m_components;
	};
}
