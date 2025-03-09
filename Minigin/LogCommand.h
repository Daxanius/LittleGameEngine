#pragma once

#include <string>

#include "Command.h"

namespace dae {
	class LogCommand final : public Command {
	public:
		LogCommand(std::string logMessage);

		void Execute() override;
	private:
		std::string m_logMessage;
	};
}