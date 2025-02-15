#include "TransformComponent.h"
#include "SDL.h"

dae::TransformComponent::TransformComponent() : Component() {
	SetPosition(0.f, 0.f, 0.f);
}

dae::TransformComponent::TransformComponent(const float x, const float y,  const float z) : Component() {
	SetPosition(x, y, z);
}

void dae::TransformComponent::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}
