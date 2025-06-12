#pragma once

#include <string>
#include "Command.h"

namespace dae {
	class ChangeSceneCommand : public Command {
	public:
		ChangeSceneCommand(const std::string& scene);

		void Execute() override;

	private:
		std::string m_pScene;;
	};
}