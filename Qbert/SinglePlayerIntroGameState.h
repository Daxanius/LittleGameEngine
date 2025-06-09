#pragma once
#include "AbstractGameState.h"
#include "Scene.h"
#include <memory>

namespace dae {
	class SinglePlayerIntroGameState final : public AbstractGameState {
	public:
		SinglePlayerIntroGameState();

		void OnEnter() override;

		SinglePlayerIntroGameState(const SinglePlayerIntroGameState&) = delete;
		SinglePlayerIntroGameState& operator=(const SinglePlayerIntroGameState&) = delete;
		SinglePlayerIntroGameState(SinglePlayerIntroGameState&&) = delete;
		SinglePlayerIntroGameState& operator=(SinglePlayerIntroGameState&&) = delete;
		~SinglePlayerIntroGameState() = default;
	private:
		std::shared_ptr<AbstractGameState> m_pSinglePlayerState;
		std::shared_ptr<Scene> m_pTutorialScene;
	};
}
