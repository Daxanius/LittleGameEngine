#include "LogCommand.h"

#include <iostream>

dae::LogCommand::LogCommand(std::string logMessage) : m_logMessage(logMessage) {
}

void dae::LogCommand::Execute() {
	std::cout << m_logMessage << "\n";
}
