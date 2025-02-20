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
		virtual void PostUpdate()  = 0; // Used to remove objects if they have been deleted
		virtual void Render() const = 0;

	protected:
		explicit BaseComponent(GameObject& pOwner);

		GameObject& GetOwner();

	private:
		GameObject* m_pOwner;
	};
}