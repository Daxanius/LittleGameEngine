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
		CoilyStateBall(CoilyComponent* pCoilyComponent);

		void OnEnter() override;
		void Update(float deltaTime) override;
		void OnExit() override;

		CoilyStateBall(const CoilyStateBall&) = delete;
		CoilyStateBall& operator=(const CoilyStateBall&) = delete;
		CoilyStateBall(CoilyStateBall&&) = delete;
		CoilyStateBall& operator=(CoilyStateBall&&) = delete;
		~CoilyStateBall() = default;
	private:
		GridMovementComponent* m_pGridMovementComponent{};
		SpriteComponent* m_pSpriteComponent{};
		GridNavigationComponent* m_pGridNavigationComponent{};

		std::shared_ptr<CoilyBallMovementObserver> m_pCoilyBallMovementObserver{};
	};
}
