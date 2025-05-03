#pragma once

#include <string>
#include "Command.h"
#include "Scene.h"

namespace dae {
	class LoadSceneCommand : public Command {
	public:
		LoadSceneCommand(std::shared_ptr<Scene> sceneToLoad);

		void Execute() override;

	private:
		std::shared_ptr<Scene> m_pSceneToLoad;
	};
}