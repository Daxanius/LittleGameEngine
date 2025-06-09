#pragma once
#include "BaseComponent.h"
#include "GameObject.h"

namespace dae {
	class RotatorComponent final : public BaseComponent {
	public:
		RotatorComponent(GameObject& pOwner, float speed, float radius);

		void FixedUpdate() override {};

		void Update(float deltaTime) override;

		void PostUpdate() override {};
		void Render() override {};


		RotatorComponent(const RotatorComponent&) = delete;
		RotatorComponent& operator=(const RotatorComponent&) = delete;
		RotatorComponent(RotatorComponent&&) = delete;
		RotatorComponent& operator=(RotatorComponent&&) = delete;
		~RotatorComponent() = default;
	private:
		float m_progress{};
		float m_speed{};
		float m_radius{};
	};
}