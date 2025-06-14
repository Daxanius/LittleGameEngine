#pragma once
#include "GridMovementComponent.h"
#include "ScoreComponent.h"
#include "Level.h"
#include <Scene.h>
#include <memory>

namespace dae {
	class CoopLevelScene : public Scene {
	public:
		CoopLevelScene(int level, int scoreP1, int scoreP2);

		void OnSetup();

		void OnEnter();

		CoopLevelScene(const CoopLevelScene&) = delete;
		CoopLevelScene& operator=(const CoopLevelScene&) = delete;
		CoopLevelScene(CoopLevelScene&&) = delete;
		CoopLevelScene& operator=(CoopLevelScene&&) = delete;
		~CoopLevelScene() = default;
	private:
		GridMovementComponent* m_pPlayer1MovementComponent{};
		GridMovementComponent* m_pPlayer2MovementComponent{};
		ScoreComponent* m_pPlayer1ScoreComponent{};
		ScoreComponent* m_pPlayer2ScoreComponent{};
		Level m_levelInfo{};

		int m_scoreP1;
		int m_scoreP2;
		int m_level;
	};
}
