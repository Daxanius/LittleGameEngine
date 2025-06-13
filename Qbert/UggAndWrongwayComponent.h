#pragma once
#include <BaseComponent.h>
#include "GridMovementComponent.h"
#include "GridNavigationComponent.h"
#include "LevelComponent.h"

namespace dae {
	class UggAndWrongwayComponent final : public BaseComponent {
	public:
		UggAndWrongwayComponent(GameObject& pOwner, LevelComponent* pLevelComponent, bool isUgg);

		void FixedUpdate() override {};
		void Update(float deltaTime) override;
		void PostUpdate() override {};
		void Render() override {};
	private:
		GridMovementComponent* m_pOwnMovementComponent{};
		GridNavigationComponent* m_pNavigationComponent{};
		LevelComponent* m_pLevelComponent{};

		bool m_isUgg{};
	};
}
