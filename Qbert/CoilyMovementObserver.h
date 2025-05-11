#pragma once
#include "Observer.h"
#include "CoilyComponent.h"	
#include "GridMovementComponent.h"

namespace dae {
	class CoilyMovementObserver : public Observer {
	public:
		CoilyMovementObserver(CoilyComponent* pCoilyComponent, GridMovementComponent* pTargetMovementComponent);

		void Notify(Event event) override;

	private:
		CoilyComponent* m_pCoilyComponent{};
		GridMovementComponent* m_pTargetMovementComponent{};
	};
}

