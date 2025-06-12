#include "NextLevelCommand.h"
#include "SceneManager.h"
#include "LevelDisplayScene.h"
#include <memory>

dae::NextLevelCommand::NextLevelCommand(ScoreComponent* pScoreComponent, int level)
	: m_pScoreComponent(pScoreComponent), m_level(level) {
}

void dae::NextLevelCommand::Execute() {
	auto scene{ std::make_unique<LevelDisplayScene>(m_level, m_pScoreComponent->GetScore()) };
	SceneManager::GetInstance().AddScene(std::move(scene));
	SceneManager::GetInstance().SetScene("LevelDisplay");
}
