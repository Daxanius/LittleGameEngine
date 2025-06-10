#pragma once
#include "AbstractGameState.h"
#include "GridMovementComponent.h"
#include "TextInputComponent.h"
#include "ScoreComponent.h"
#include "Scene.h"
#include <memory>

namespace dae {
	class SinglePlayerScoreDisplayState final : public AbstractGameState {
	public:
		SinglePlayerScoreDisplayState();

		void OnEnter() override;

		SinglePlayerScoreDisplayState(const SinglePlayerScoreDisplayState&) = delete;
		SinglePlayerScoreDisplayState& operator=(const SinglePlayerScoreDisplayState&) = delete;
		SinglePlayerScoreDisplayState(SinglePlayerScoreDisplayState&&) = delete;
		SinglePlayerScoreDisplayState& operator=(SinglePlayerScoreDisplayState&&) = delete;
		~SinglePlayerScoreDisplayState() = default;
	private:
		std::shared_ptr<Scene> m_pScene;

		TextInputComponent* m_pTextInputComponent{};
	};
}
