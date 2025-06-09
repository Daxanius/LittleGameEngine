#pragma once
#include "GameObject.h"

namespace dae {
	class BaseComponent {
	public:
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void FixedUpdate() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void PostUpdate()  = 0; // Used to remove components if they have been deleted
		virtual void Render() = 0;

		GameObject& GetOwner();

		void Enable();
		void Disable();
		bool IsEnabled() const;

		// Gets the component from the object
		template<typename ComponentType>
		requires std::derived_from<ComponentType, BaseComponent>
		[[nodiscard]] inline ComponentType* GetComponent() const {
			return m_pOwner->GetComponent<ComponentType>();
		}

		// Adds a component to the object
		template<typename ComponentType, typename... Args>
		requires std::derived_from<ComponentType, BaseComponent>
		inline ComponentType* AddComponent(Args&&... args) {
			return m_pOwner->AddComponent<ComponentType>(std::forward<Args>(args));
		}

		// Checks if the object has a component
		template<typename ComponentType>
		requires std::derived_from<ComponentType, BaseComponent>
		[[nodiscard]] bool HasComponent() const {
			return m_pOwner->HasComponent<ComponentType>();
		}

		void Destroy();
		[[nodiscard]] bool IsDestroyed() const;
	protected:
		explicit BaseComponent(GameObject& pOwner);

	private:
		GameObject* m_pOwner;
		bool m_destroyed{ false };
		bool m_enabled{ true };
	};
}