#pragma once
#include <Observer.h>
#include "CoilyComponent.h"
#include "GridMovementComponent.h"
#include "SpriteComponent.h"

namespace dae {
	class CoilySnakeMovementObserver : public Observer {
	public:
		CoilySnakeMovementObserver(CoilyComponent* pCoilyComponent, GridMovementComponent* pTargetMovementComponent);

		void Notify(const Event& event) override;

	private:
		enum class Direction {
			Up,
			Down,
			Left,
			Right
		};

		CoilyComponent* m_pCoilyComponent{};
		GridMovementComponent* m_pTargetMovementComponent{};
		SpriteComponent* m_pSpriteComponent{};

		Direction m_lastDirection{ Direction::Up };
	};
}