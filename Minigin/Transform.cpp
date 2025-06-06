#include "Transform.h"
#include "SDL.h"

dae::Transform::Transform() {
	SetPosition(0.f, 0.f, 0.f);
}

dae::Transform::Transform(const float x, const float y,  const float z) {
	SetPosition(x, y, z);
}

dae::Transform::Transform(const glm::vec2& position) {
	SetPosition(position.x, position.y, 0.f);
}

dae::Transform::Transform(const glm::vec3& position) {
	m_position = position;
}

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

void dae::Transform::SetPosition(const glm::vec3& position) {
	m_position = position;
}

dae::Transform dae::Transform::operator+(const Transform& other) const {
	return Transform(m_position.x + other.m_position.x,
									 m_position.y + other.m_position.y,
									 m_position.z + other.m_position.z);
}

dae::Transform dae::Transform::operator-(const Transform& other) const {
	return Transform(m_position.x - other.m_position.x,
									 m_position.y - other.m_position.y,
									 m_position.z - other.m_position.z);
}
