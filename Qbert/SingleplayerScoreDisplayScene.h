#pragma once
#include "GridMovementComponent.h"
#include "TextInputComponent.h"
#include "ScoreComponent.h"
#include "Scene.h"
#include <memory>

namespace dae {
	class SingleplayerScoreDisplayScene final : public Scene {
	public:
		SingleplayerScoreDisplayScene(int score = 0);

		void OnSetup() override;
		void OnEnter() override;

		SingleplayerScoreDisplayScene(const SingleplayerScoreDisplayScene&) = delete;
		SingleplayerScoreDisplayScene& operator=(const SingleplayerScoreDisplayScene&) = delete;
		SingleplayerScoreDisplayScene(SingleplayerScoreDisplayScene&&) = delete;
		SingleplayerScoreDisplayScene& operator=(SingleplayerScoreDisplayScene&&) = delete;
		~SingleplayerScoreDisplayScene() = default;
	private:
		int m_score{};

		TextInputComponent* m_pTextInputComponent{};
	};
}
