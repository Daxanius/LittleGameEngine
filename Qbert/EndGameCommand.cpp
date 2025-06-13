#include "EndGameCommand.h"
#include "SceneManager.h"
#include "LevelDisplayScene.h"
#include <memory>
#include "SingleplayerScoreDisplayScene.h"

dae::EndGameCommand::EndGameCommand(ScoreComponent* pScoreComponent) 
	: m_pScoreComponent(pScoreComponent){
}

void dae::EndGameCommand::Execute() {
	auto scene{ std::make_unique<SingleplayerScoreDisplayScene>(m_pScoreComponent->GetScore()) };
	SceneManager::GetInstance().AddScene(std::move(scene));
	SceneManager::GetInstance().SetScene("SingleplayerScoreDisplay");
}
