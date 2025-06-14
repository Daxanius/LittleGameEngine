#pragma once
#include <Scene.h>
#include "TimerComponent.h"
#include "AbstractSoundSystem.h"
#include "ServiceLocator.h"
#include "Level.h"

namespace dae {
	class LevelDisplayScene : public Scene {
	public:
		LevelDisplayScene(LevelType levelType, int level = 0, int scoreP1 = 0, int scoreP2 = 0);

		void OnSetup() override;
		void OnEnter() override;

	private:
		int m_level{};
		int m_scoreP1{};
		int m_scoreP2{};

		TimerComponent* m_pTimerComponent{};
		LevelType m_levelType{};
		SoundId m_enterSfx{};
	};
}


