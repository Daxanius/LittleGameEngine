#include "ChangeGameStateCommand.h"
#include "Qbert.h"

dae::ChangeGameStateCommand::ChangeGameStateCommand(std::shared_ptr<AbstractGameState> state) : Command(), m_state(state) {
}

void dae::ChangeGameStateCommand::Execute() {
	Qbert::GetInstance().SetState(m_state);
}
