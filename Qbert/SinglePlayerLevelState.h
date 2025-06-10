#pragma once
#include "AbstractGameState.h"
#include "GridMovementComponent.h"
#include "ScoreComponent.h"
#include "Scene.h"
#include <memory>

namespace dae {
	class SinglePlayerGameState final : public AbstractGameState {
	public:
		SinglePlayerGameState();

		void OnEnter() override;

		SinglePlayerGameState(const SinglePlayerGameState&) = delete;
		SinglePlayerGameState& operator=(const SinglePlayerGameState&) = delete;
		SinglePlayerGameState(SinglePlayerGameState&&) = delete;
		SinglePlayerGameState& operator=(SinglePlayerGameState&&) = delete;
		~SinglePlayerGameState() = default;
	private:
		void MakePauseScene();
		void MakeGameScene();
		void MakeLevelDisplayScene();

		std::shared_ptr<Scene> m_pScene;
		std::shared_ptr<Scene> m_pPauseScene;
		std::shared_ptr<Scene> m_pLevelDisplayScene;

		GridMovementComponent* m_pPlayerMovementComponent{};

		int m_score;
		int m_level;
	};
}


