#pragma once
#include "BaseComponent.h"

namespace dae {
	// Adds added movement every next frame
	class MoveComponent final : public BaseComponent {
	public:
		MoveComponent(GameObject& pOwner, float speed);

		void FixedUpdate() override {};

		void Update(float deltaTime) override;

		void PostUpdate() override;
		void Render() override {};

		void AddDirection(glm::vec2 direction);
	private:
		glm::vec2 m_direction;
		float m_speed;
	};
}
