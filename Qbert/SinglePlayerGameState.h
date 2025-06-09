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
		void MakeGameOverScene();

		std::shared_ptr<Scene> m_pScene;
		std::shared_ptr<Scene> m_pPauseScene;
		std::shared_ptr<Scene> m_pGameOverScene;

		GridMovementComponent* m_pPlayerMovementComponent{};
		ScoreComponent* m_pScoreComponent{};
	};
}


