#pragma once
#include "AbstractCoilyState.h"
#include "GridMovementComponent.h"
#include "SpriteComponent.h"
#include "GridNavigationComponent.h"
#include "CoilyBallMovementObserver.h"
#include <memory>

namespace dae {
	class CoilyStateBall final : public AbstractCoilyState {
	public:
		CoilyStateBall(CoilyComponent* pCoilyComponent, GridMovementComponent* pTargetMovementComponent);

		void OnEnter() override;
		void Update(float deltaTime) override;
		void OnExit() override;

	private:
		GridMovementComponent* m_pGridMovementComponent{};
		GridMovementComponent* m_pTargetMovementComponent{};
		SpriteComponent* m_pSpriteComponent{};
		GridNavigationComponent* m_pGridNavigationComponent{};

		std::shared_ptr<CoilyBallMovementObserver> m_pCoilyBallMovementObserver{};
	};
}
