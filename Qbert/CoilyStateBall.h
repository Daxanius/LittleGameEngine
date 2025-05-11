#pragma once
#include "AbstractCoilyState.h"
#include "GridMovementComponent.h"
#include "SpriteComponent.h"
#include "GridNavigationComponent.h"

namespace dae {
	class CoilyStateBall final : public AbstractCoilyState {
	public:
		CoilyStateBall(CoilyComponent* pCoilyComponent);

		void OnEnter() override;
		void Update(float deltaTime) override;
		void OnExit() override;

	private:
		GridMovementComponent* m_pGridMovementComponent{};
		SpriteComponent* m_pSpriteComponent{};
		GridNavigationComponent* m_pGridNavigationComponent{};
	};
}
