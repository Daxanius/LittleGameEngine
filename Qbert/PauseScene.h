#pragma once
#include <Scene.h>

namespace dae {
	class PauseScene final : public Scene {
	public:
		PauseScene();
	
		virtual void OnSetup();
	};
}
