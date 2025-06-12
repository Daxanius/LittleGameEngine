#pragma once
#include <Scene.h>
#include "TimerComponent.h"

namespace dae {
	class LevelDisplayScene : public Scene {
	public:
		LevelDisplayScene();

		void OnSetup() override;
		void OnEnter() override;

	private:
		int m_level{};

		TimerComponent* m_pTimerComponent{};
	};
}


