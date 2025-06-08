#pragma once
#include <Scene.h>
#include <Command.h>
#include <memory>

namespace dae {
	class PauseCommand : public Command {
	public:
		PauseCommand(std::shared_ptr<Scene> pPauseScene, std::shared_ptr<Scene> pGameScene);

		void Execute() override;

	private:
		std::shared_ptr<Scene> m_pPauseScene;
		std::shared_ptr<Scene> m_pGameScene;

		bool m_isPaused{};
	};
}


