#include "MoveComponent.h"

dae::MoveComponent::MoveComponent(GameObject& pOwner, float speed) : BaseComponent(pOwner), m_speed(speed), m_direction(glm::vec3(0, 0, 0)) {
}

void dae::MoveComponent::Update(float deltaTime) {
	Transform transform{ GetOwner().GetLocalTransform() };
	const glm::uvec3 position{};
	transform.SetPosition(transform.GetPosition() + glm::vec3(m_direction, 0.0f) * m_speed * deltaTime);
	GetOwner().SetLocalTransform(transform);
}

void dae::MoveComponent::PostUpdate() {
	m_direction = glm::vec3(0, 0, 0);
}

void dae::MoveComponent::AddDirection(glm::vec2 direction) {
	m_direction += direction;

	// Only normalize if m_direction is not zero
	if (glm::length(m_direction) > 0.0001f) {
		m_direction = glm::normalize(m_direction);
	} else {
		m_direction = glm::vec2(0, 0); // Keep it zero to avoid NaN issues
	}
}
