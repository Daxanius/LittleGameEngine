#pragma once
#include <BaseComponent.h>
#include "GridMovementComponent.h"

namespace dae {
	class GridNavigationComponent : public BaseComponent {
	public:
		GridNavigationComponent(GameObject& pOwner, float jumpCooldown);

		void FixedUpdate() override {};
		void Update(float deltaTime) override;
		void PostUpdate() override {};
		void Render() override {};

		void SetTarget(int row, int col);
		bool HasArrived() const;
	private:
		GridMovementComponent* m_pMovementComponent{};

		int m_targetRow{};
		int m_targetCol{};

		float m_jumpCooldown;
		float m_timeSinceLastJump{};
	};
}

