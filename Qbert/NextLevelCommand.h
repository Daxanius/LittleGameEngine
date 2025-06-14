#pragma once
#include "Command.h"
#include "ScoreComponent.h"
#include "Level.h"

namespace dae {
	class NextLevelCommand final : public Command {
	public:
		NextLevelCommand(LevelType type, int level, ScoreComponent* pScoreComponentP1, ScoreComponent* pScoreComponentP2 = nullptr);

		// Inherited via Command
		void Execute() override;
	private:
		void GoToSinglePlayerLevel();
		void GoToCoopLevel();

		ScoreComponent* m_pScoreComponentP1{};
		ScoreComponent* m_pScoreComponentP2{};

		int m_level{};
		LevelType m_levelType{};
	};
}
