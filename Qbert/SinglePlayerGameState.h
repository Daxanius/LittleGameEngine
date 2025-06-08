#pragma once
#include "AbstractGameState.h"
#include "GridMovementComponent.h"
#include "Scene.h"
#include <memory>

namespace dae {
	class SinglePlayerGameState final : public AbstractGameState {
	public:
		SinglePlayerGameState();

		void OnEnter() override;

	private:
		void MakePauseScene();
		void MakeGameScene();

		std::shared_ptr<Scene> m_pScene;
		std::shared_ptr<Scene> m_pPauseScene;

		GridMovementComponent* m_pPlayerMovementComponent{};
	};
}


