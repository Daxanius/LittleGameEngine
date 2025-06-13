#pragma once
#include <Scene.h>
#include "TimerComponent.h"
#include "AbstractSoundSystem.h"
#include "ServiceLocator.h"

namespace dae {
	class LevelDisplayScene : public Scene {
	public:
		LevelDisplayScene(int level = 0, int score = 0);

		void OnSetup() override;
		void OnEnter() override;

	private:
		int m_level{};
		int m_score{};

		TimerComponent* m_pTimerComponent{};

		SoundId m_enterSfx{};
	};
}


