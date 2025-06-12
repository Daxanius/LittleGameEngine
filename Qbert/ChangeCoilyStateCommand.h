#pragma once
#include "Command.h"
#include "AbstractCoilyState.h"
#include "CoilyComponent.h"
#include <memory>

namespace dae {
	class ChangeCoilyStateCommand final : public Command {
	public:
		ChangeCoilyStateCommand(std::shared_ptr<AbstractCoilyState> pState, CoilyComponent* pCoilyComponent);

		void Execute() override;
	private:
		std::shared_ptr<AbstractCoilyState> m_state;
		CoilyComponent* m_pCoilyComponent{};
	};
}

