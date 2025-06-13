#pragma once
#include "Command.h"
#include "SceneManager.h"
#include "LevelDisplayScene.h"
#include "ScoreComponent.h"
#include <memory>

namespace dae {
	class EndGameCommand final : public Command {
	public:
		EndGameCommand(ScoreComponent* pScoreComponent);

		void Execute() override;
	private:
		ScoreComponent* m_pScoreComponent;
	};
}
