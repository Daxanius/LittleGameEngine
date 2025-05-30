#pragma once
#include "AbstractCoilyState.h"
#include "GridMovementComponent.h"
#include "SpriteComponent.h"
#include "GridNavigationComponent.h"
#include "CoilySnakeMovementObserver.h"
#include <memory>

namespace dae {
	class CoilyStateSnake : public AbstractCoilyState {
	public:
		CoilyStateSnake(CoilyComponent* pCoilyComponent, GridMovementComponent* pTargetMovement);

		void OnEnter() override;
		void Update(float deltaTime) override;
		void OnExit() override;

	private:
		GridMovementComponent* m_pGridMovementComponent{};
		SpriteComponent* m_pSpriteComponent{};
		GridNavigationComponent* m_pGridNavigationComponent{};
		GridMovementComponent* m_pTargetMovementComponent{};

		std::shared_ptr<CoilySnakeMovementObserver> m_pCoilySnakeMovementObserver{};
	};
}
