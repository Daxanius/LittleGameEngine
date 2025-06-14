#pragma once
#include <Scene.h>

namespace dae {
	class PauseScene final : public Scene {
	public:
		PauseScene(const std::string& resumeScene);
	
		virtual void OnSetup();
		virtual void OnEnter();


		PauseScene(const PauseScene&) = delete;
		PauseScene& operator=(const PauseScene&) = delete;
		PauseScene(PauseScene&&) = delete;
		PauseScene& operator=(PauseScene&&) = delete;
		~PauseScene() = default;
	private:
		std::string m_resumeScene;
	};
}
