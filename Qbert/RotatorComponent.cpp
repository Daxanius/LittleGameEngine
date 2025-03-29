#include "RotatorComponent.h"

dae::RotatorComponent::RotatorComponent(GameObject& pOwner, float speed, float radius) : BaseComponent(pOwner), m_radius{ radius }, m_speed{ speed } {
}

void dae::RotatorComponent::Update(float deltaTime) {
	GameObject& pOwner{ GetOwner() };

	pOwner.SetLocalTransform(Transform(std::cosf(m_progress * m_speed) * m_radius, std::sinf(m_progress * m_speed) * m_radius));
	m_progress += deltaTime;
}

