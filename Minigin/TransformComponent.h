#pragma once
#include <glm.hpp>
#include "BaseComponent.h"

namespace dae
{
	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent(GameObject& pOwner);
		TransformComponent(GameObject& pOwner, float x, float y, float z = 0.f);

		void SetPosition(float x, float y, float z);

		const glm::vec3& GetPosition() const { return m_position; };
		
		void FixedUpdate() override {};
		void Update(float) override {};
		void PostUpdate() override {};
		void Render() const override {};
	private:
		glm::vec3 m_position;
	};
}
