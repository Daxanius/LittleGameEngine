#pragma once
#include <Scene.h>
#include <memory>

namespace dae {
	class CoopIntroScene : public Scene {
	public:
		CoopIntroScene();

		void OnSetup() override;
		void OnEnter() override;

		CoopIntroScene(const CoopIntroScene&) = delete;
		CoopIntroScene& operator=(const CoopIntroScene&) = delete;
		CoopIntroScene(CoopIntroScene&&) = delete;
		CoopIntroScene& operator=(CoopIntroScene&&) = delete;
		~CoopIntroScene() = default;
	};
}

