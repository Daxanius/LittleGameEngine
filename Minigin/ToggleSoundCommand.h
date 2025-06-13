#pragma once
#include "Command.h"

namespace dae {
	class ToggleSoundCommand final : public Command {
	public:
		ToggleSoundCommand() = default;

		void Execute() override;
	};
}


