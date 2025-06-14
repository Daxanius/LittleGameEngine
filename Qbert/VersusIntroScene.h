#pragma once
#include "Scene.h"

namespace dae {
	class VersusIntroScene final : public Scene {
	public:
		VersusIntroScene();

		void OnSetup() override;
		void OnEnter() override;

		VersusIntroScene(const VersusIntroScene&) = delete;
		VersusIntroScene& operator=(const VersusIntroScene&) = delete;
		VersusIntroScene(VersusIntroScene&&) = delete;
		VersusIntroScene& operator=(VersusIntroScene&&) = delete;
		~VersusIntroScene() = default;
	};
}
