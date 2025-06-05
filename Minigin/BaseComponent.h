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