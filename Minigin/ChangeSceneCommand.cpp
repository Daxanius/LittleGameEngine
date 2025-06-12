#include "ChangeSceneCommand.h"
#include "SceneManager.h"

dae::ChangeSceneCommand::ChangeSceneCommand(const std::string& scene) 
 : m_pScene(scene) {
}

void dae::ChangeSceneCommand::Execute() {
	SceneManager::GetInstance().SetScene(m_pScene);
}
