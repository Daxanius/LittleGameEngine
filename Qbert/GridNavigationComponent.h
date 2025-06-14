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

		void Enable();
		void Disable();
		bool IsEnabled() const;


		GridNavigationComponent(const GridNavigationComponent&) = delete;
		GridNavigationComponent& operator=(const GridNavigationComponent&) = delete;
		GridNavigationComponent(GridNavigationComponent&&) = delete;
		GridNavigationComponent& operator=(GridNavigationComponent&&) = delete;
		~GridNavigationComponent() = default;
	private:
		GridMovementComponent* m_pMovementComponent{};

		bool m_enabled;

		int m_targetRow{};
		int m_targetCol{};

		float m_jumpCooldown;
		float m_timeSinceLastJump{};
	};
}

