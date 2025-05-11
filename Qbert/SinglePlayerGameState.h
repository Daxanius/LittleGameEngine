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
		std::shared_ptr<Scene> m_pScene;

		GridMovementComponent* m_pPlayerMovementComponent{};
	};
}


