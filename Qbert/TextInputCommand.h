#pragma once
#include <Command.h>
#include "TextInputComponent.h"

namespace dae {
	class TextInputCommand final : public Command {
	public:
		enum class InputCommand {
			Up,
			Down,
			Left,
			Right
		};

		TextInputCommand(TextInputComponent* pComponent, InputCommand command);

		void Execute() override;

	private:
		InputCommand m_command;
		TextInputComponent* m_pComponent;
	};
}

