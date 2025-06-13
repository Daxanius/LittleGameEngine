#pragma once
#include <BaseComponent.h>
#include "GridMovementComponent.h"
#include "GridNavigationComponent.h"
#include "LevelComponent.h"

namespace dae {
	class SlickAndSlamComponent final : public BaseComponent {
	public:
		SlickAndSlamComponent(GameObject& pOwner, LevelComponent* pLevelComponent);

		void FixedUpdate() override {};
		void Update(float deltaTime) override;
		void PostUpdate() override {};
		void Render() override {};

	private:
		GridMovementComponent* m_pOwnMovementComponent{};
		GridNavigationComponent* m_pNavigationComponent{};
		LevelComponent* m_pLevelComponent{};
	};
}

