#pragma once
#include "GridMovementComponent.h"
#include "ScoreComponent.h"
#include "Scene.h"
#include "Level.h"
#include <memory>

namespace dae {
	class SingleplayerLevelScene final : public Scene {
	public:
		SingleplayerLevelScene(int level = 0, int score = 0);

		void OnSetup() override;
		void OnEnter() override;

		SingleplayerLevelScene(const SingleplayerLevelScene&) = delete;
		SingleplayerLevelScene& operator=(const SingleplayerLevelScene&) = delete;
		SingleplayerLevelScene(SingleplayerLevelScene&&) = delete;
		SingleplayerLevelScene& operator=(SingleplayerLevelScene&&) = delete;
		~SingleplayerLevelScene() = default;
	private:
		GridMovementComponent* m_pPlayerMovementComponent{};
		Level m_levelInfo{};

		int m_score;
		int m_level;
	};
}
