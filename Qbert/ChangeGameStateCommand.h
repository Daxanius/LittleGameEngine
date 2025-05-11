#pragma once
#include "Command.h"
#include "AbstractGameState.h"

namespace dae {
	class ChangeGameStateCommand : public Command {
	public:
		ChangeGameStateCommand(std::shared_ptr<AbstractGameState> state);

		void Execute() override;

	private:
		std::shared_ptr<AbstractGameState> m_state;
	};
}
