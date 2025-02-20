#include "TransformComponent.h"
#include "SDL.h"

dae::TransformComponent::TransformComponent(GameObject& pOwner) : Component(pOwner) {
	SetPosition(0.f, 0.f, 0.f);
}

dae::TransformComponent::TransformComponent(GameObject& pOwner, const float x, const float y,  const float z) : Component(pOwner) {
	SetPosition(x, y, z);
}

void dae::TransformComponent::SetPosition(const float x, const float y, const float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}
