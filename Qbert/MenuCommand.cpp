#include "MenuCommand.h"

dae::MenuCommand::MenuCommand(SelectionMenuComponent* pSelectionMenuComponent, Action action) : Command(), m_pSelectionMenuComponent(pSelectionMenuComponent), m_action(action) {
}

void dae::MenuCommand::Execute() {
	switch (m_action) {
		case Action::Previous:
			m_pSelectionMenuComponent->PreviousOption();
			break;
		case Action::Next:
			m_pSelectionMenuComponent->NextOption();
			break;
		case Action::Confirm:
			m_pSelectionMenuComponent->ConfirmOption();
			break;
	}
}
