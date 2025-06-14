#pragma once
#include <Scene.h>
#include "TimerComponent.h"

namespace dae {
	class IntroScrene final : public Scene {
	public:
		IntroScrene();

		void OnSetup() override;
		void OnEnter() override;

	private:
		TimerComponent* m_pTimerComponent{};
	};
}
