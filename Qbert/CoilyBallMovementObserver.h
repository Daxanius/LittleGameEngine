#pragma once
#include "Observer.h"
#include "CoilyComponent.h"	
#include "GridMovementComponent.h"
#include "SpriteComponent.h"

namespace dae {
	class CoilyBallMovementObserver : public Observer {
	public:
		CoilyBallMovementObserver(CoilyComponent* pCoilyComponent, GridMovementComponent* pTargetMovementComponent);

		void Notify(Event event) override;

	private:
		CoilyComponent* m_pCoilyComponent{};
		GridMovementComponent* m_pTargetMovementComponent{};
		SpriteComponent* m_pSpriteComponent{};
	};
}

