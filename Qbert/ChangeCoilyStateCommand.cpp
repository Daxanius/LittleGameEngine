#include "ChangeCoilyStateCommand.h"

dae::ChangeCoilyStateCommand::ChangeCoilyStateCommand(std::shared_ptr<AbstractCoilyState> pState, CoilyComponent* pCoilyComponent)
	: m_pCoilyComponent(pCoilyComponent), m_state(std::move(pState))
{
}

void dae::ChangeCoilyStateCommand::Execute() {
	if (m_pCoilyComponent) {
		m_pCoilyComponent->SetState(m_state);
	}
}
