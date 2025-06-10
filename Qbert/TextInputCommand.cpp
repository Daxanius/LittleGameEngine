#include "TextInputCommand.h"

dae::TextInputCommand::TextInputCommand(TextInputComponent* pComponent, InputCommand command)
 : m_pComponent(pComponent), m_command(command) {
}

void dae::TextInputCommand::Execute() {
	switch (m_command) {
		case InputCommand::Down:
			m_pComponent->Down();
			break;
		case InputCommand::Up:
			m_pComponent->Up();
			break;
		case InputCommand::Left:
			m_pComponent->Left();
			break;
		case InputCommand::Right:
			m_pComponent->Right();
			break;
	}
}
