#pragma once
#include <Scene.h>
#include "TimerComponent.h"

namespace dae {
	class IntroScene final : public Scene {
	public:
		IntroScene();

		void OnSetup() override;
		void OnEnter() override;


		IntroScene(const IntroScene&) = delete;
		IntroScene& operator=(const IntroScene&) = delete;
		IntroScene(IntroScene&&) = delete;
		IntroScene& operator=(IntroScene&&) = delete;
		~IntroScene() = default;

	private:
		TimerComponent* m_pTimerComponent{};
	};
}
