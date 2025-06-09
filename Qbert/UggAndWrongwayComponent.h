#pragma once
#include <BaseComponent.h>
#include "GridMovementComponent.h"
#include "GridNavigationComponent.h"
#include "LevelComponent.h"

namespace dae {
	class UggAndWrongwayComponent final : public BaseComponent {
	public:
		UggAndWrongwayComponent(GameObject& pOwner, GridMovementComponent* pPlayerMovementComponent, LevelComponent* pLevelComponent);

		void FixedUpdate() override {};
		void Update(float deltaTime) override;
		void PostUpdate() override {};
		void Render() override {};
	private:
		GridMovementComponent* m_pOwnMovementComponent{};
		GridMovementComponent* m_pPlayerMovementComponent{};
		GridNavigationComponent* m_pNavigationComponent{};
		LevelComponent* m_pLevelComponent{};
	};
}
