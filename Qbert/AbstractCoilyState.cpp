#include "AbstractCoilyState.h"

dae::AbstractCoilyState::AbstractCoilyState(CoilyComponent* pCoilyComponent) : m_pCoilyComponent(pCoilyComponent) {

}

dae::CoilyComponent* dae::AbstractCoilyState::GetCoilyComponent() const {
	return m_pCoilyComponent;
}

