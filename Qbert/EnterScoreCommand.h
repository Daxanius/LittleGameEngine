#pragma once
#include "Command.h"
#include "TextInputComponent.h"

namespace dae {
	class EnterScoreCommand final : public Command {
	public:
		EnterScoreCommand(int score, TextInputComponent* pTextInputComponent);

		void Execute() override;
	private:
		TextInputComponent* m_pTextInputComponent;
		int m_score;
	};
}

