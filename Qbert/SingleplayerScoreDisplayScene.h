#pragma once
#include "GridMovementComponent.h"
#include "TextInputComponent.h"
#include "ScoreComponent.h"
#include "Scene.h"
#include <memory>

namespace dae {
	class SingleplayerScoreDisplayScene final : public Scene {
	public:
		SingleplayerScoreDisplayScene();

		void OnSetup() override;
		void OnEnter() override;

		SingleplayerScoreDisplayScene(const SingleplayerScoreDisplayScene&) = delete;
		SingleplayerScoreDisplayScene& operator=(const SingleplayerScoreDisplayScene&) = delete;
		SingleplayerScoreDisplayScene(SingleplayerScoreDisplayScene&&) = delete;
		SingleplayerScoreDisplayScene& operator=(SingleplayerScoreDisplayScene&&) = delete;
		~SingleplayerScoreDisplayScene() = default;
	private:
		TextInputComponent* m_pTextInputComponent{};
	};
}
