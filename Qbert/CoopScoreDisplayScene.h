#pragma once
#include "Scene.h"

namespace dae {
	class CoopScoreDisplayScene final : public Scene {
	public:
		CoopScoreDisplayScene(int scoreP1 = 0, int scoreP2 = 0);

		void OnSetup() override;
		void OnEnter() override;

		CoopScoreDisplayScene(const CoopScoreDisplayScene&) = delete;
		CoopScoreDisplayScene& operator=(const CoopScoreDisplayScene&) = delete;
		CoopScoreDisplayScene(CoopScoreDisplayScene&&) = delete;
		CoopScoreDisplayScene& operator=(CoopScoreDisplayScene&&) = delete;
		~CoopScoreDisplayScene() = default;

	private:
		int m_scoreP1{};
		int m_scoreP2{};
	};
}
