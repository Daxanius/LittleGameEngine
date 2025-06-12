#pragma once
#include <Scene.h>

namespace dae {
	class PauseScene final : public Scene {
	public:
		PauseScene(const std::string& resumeScene);
	
		virtual void OnSetup();
		virtual void OnEnter();
	private:
		std::string m_resumeScene;
	};
}
