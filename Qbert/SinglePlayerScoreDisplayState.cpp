#include "SinglePlayerScoreDisplayState.h"

dae::SinglePlayerScoreDisplayState::SinglePlayerScoreDisplayState() 
	: m_pScene(std::make_unique<Scene>("ScoreDisplay")) {

}

void dae::SinglePlayerScoreDisplayState::OnEnter() {
		SceneManager::GetInstance().SetScene(m_pScene);
}
