#pragma once
#include "Command.h"
#include "SceneManager.h"
#include "LevelDisplayScene.h"
#include "ScoreComponent.h"
#include "Level.h"
#include <memory>

namespace dae {
	class EndGameCommand final : public Command {
	public:
		EndGameCommand(LevelType levelType, ScoreComponent* pScoreComponentP1, ScoreComponent* pScoreComponentP2 = nullptr);

		void Execute() override;
	private:
		void GoToEndscreenSingleplayer();
		void GoToEndscreenCoop();

		ScoreComponent* m_pScoreComponentP1{};
		ScoreComponent* m_pScoreComponentP2{};

		LevelType m_levelType;
	};
}
