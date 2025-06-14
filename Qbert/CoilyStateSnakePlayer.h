#pragma once
#include "AbstractCoilyState.h"
#include "GridMovementComponent.h"
#include "SpriteComponent.h"
#include "GridNavigationComponent.h"
#include "CoilySnakeMovementObserver.h"
#include <memory>

namespace dae {
	class CoilyStateSnakePlayer : public AbstractCoilyState {
		public:
			CoilyStateSnakePlayer(CoilyComponent* pCoilyComponent);

			void OnEnter() override;
			void Update(float deltaTime) override;
			void OnExit() override;


			CoilyStateSnakePlayer(const CoilyStateSnakePlayer&) = delete;
			CoilyStateSnakePlayer& operator=(const CoilyStateSnakePlayer&) = delete;
			CoilyStateSnakePlayer(CoilyStateSnakePlayer&&) = delete;
			CoilyStateSnakePlayer& operator=(CoilyStateSnakePlayer&&) = delete;
			~CoilyStateSnakePlayer() = default;

	private:
		GridMovementComponent* m_pGridMovementComponent{};
		SpriteComponent* m_pSpriteComponent{};

		std::shared_ptr<CoilySnakeMovementObserver> m_pCoilySnakeMovementObserver{};
	};
}
