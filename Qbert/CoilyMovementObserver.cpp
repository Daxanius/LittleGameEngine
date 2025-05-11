#include "CoilyMovementObserver.h"
#include "hash.h"
#include "CoilyStateSnake.h"

dae::CoilyMovementObserver::CoilyMovementObserver(CoilyComponent* pCoilyComponent, GridMovementComponent* pTargetMovementComponent) 
	: m_pCoilyComponent(pCoilyComponent), m_pTargetMovementComponent(pTargetMovementComponent) {
}

void dae::CoilyMovementObserver::Notify(Event event) {
	switch (event.id) {
		case (make_sdbm_hash("arrive")):
			m_pCoilyComponent->SetState(std::make_shared<CoilyStateSnake>(m_pCoilyComponent, m_pTargetMovementComponent));
			break;
	}
}
