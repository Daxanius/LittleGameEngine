#pragma once
#include "Command.h"
#include "ScoreComponent.h"

namespace dae {
	class NextLevelCommand final : public Command {
	public:
		NextLevelCommand(ScoreComponent* pScoreComponent, int level);

		// Inherited via Command
		void Execute() override;
	private:
		ScoreComponent* m_pScoreComponent;

		int m_level;
	};
}
