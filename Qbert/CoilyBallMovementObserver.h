#pragma once
#include "Observer.h"
#include "CoilyComponent.h"	
#include "GridMovementComponent.h"
#include "SpriteComponent.h"

namespace dae {
	class CoilyBallMovementObserver : public Observer {
	public:
		CoilyBallMovementObserver(CoilyComponent* pCoilyComponent);

		void Notify(const Event& event) override;

	private:
		CoilyComponent* m_pCoilyComponent{};
		SpriteComponent* m_pSpriteComponent{};
	};
}

