#include "PauseCommand.h"
#include "SceneManager.h"

dae::PauseCommand::PauseCommand(std::shared_ptr<Scene> pPauseScene, std::shared_ptr<Scene> pGameScene)
 : m_pPauseScene(pPauseScene), m_pGameScene(pGameScene) {
}

void dae::PauseCommand::Execute() {
	if (m_isPaused) {
		SceneManager::GetInstance().SetScene(m_pGameScene);
		m_isPaused = false;
		return;
	}

	SceneManager::GetInstance().SetScene(m_pPauseScene);
	m_isPaused = true;
}
