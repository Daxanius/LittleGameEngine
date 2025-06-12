#pragma once
#include "Scene.h"
#include <memory>

namespace dae {
	class SingleplayerIntroScene final : public Scene {
	public:
		SingleplayerIntroScene();

		void OnSetup() override;
		void OnEnter() override;

		SingleplayerIntroScene(const SingleplayerIntroScene&) = delete;
		SingleplayerIntroScene& operator=(const SingleplayerIntroScene&) = delete;
		SingleplayerIntroScene(SingleplayerIntroScene&&) = delete;
		SingleplayerIntroScene& operator=(SingleplayerIntroScene&&) = delete;
		~SingleplayerIntroScene() = default;
	};
}
