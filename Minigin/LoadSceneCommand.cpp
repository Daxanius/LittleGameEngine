#include "LoadSceneCommand.h"

dae::LoadSceneCommand::LoadSceneCommand(std::shared_ptr<Scene> sceneToLoad) : m_pSceneToLoad(sceneToLoad) {
}

void dae::LoadSceneCommand::Execute() {
	SceneManager::GetInstance().SetScene(m_pSceneToLoad);
}
