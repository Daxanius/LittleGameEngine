#pragma once
#include <glm.hpp>
#include "Component.h"

namespace dae
{
	class TransformComponent final : public Component
	{
	public:
		TransformComponent();
		TransformComponent(float x, float y, float z = 0.f);

		void SetPosition(float x, float y, float z);

		const glm::vec3& GetPosition() const { return m_Position; };
	private:
		glm::vec3 m_Position;
	};
}
