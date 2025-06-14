#include "EndGameCommand.h"
#include "SceneManager.h"
#include "LevelDisplayScene.h"
#include <memory>
#include "SingleplayerScoreDisplayScene.h"
#include "CoopScoreDisplayScene.h"

dae::EndGameCommand::EndGameCommand(LevelType levelType, ScoreComponent* pScoreComponentP1, ScoreComponent* pScoreComponentP2) 
	: m_levelType(levelType), m_pScoreComponentP1(pScoreComponentP1), m_pScoreComponentP2(pScoreComponentP2) {
}

void dae::EndGameCommand::Execute() {
	switch (m_levelType) {
		case LevelType::Singleplayer:
			GoToEndscreenSingleplayer();
			break;
		case LevelType::Coop:
			GoToEndscreenCoop();
			break;
	}
}

void dae::EndGameCommand::GoToEndscreenSingleplayer() {
	auto scene{ std::make_unique<SingleplayerScoreDisplayScene>(m_pScoreComponentP1->GetScore()) };
	SceneManager::GetInstance().AddScene(std::move(scene));
	SceneManager::GetInstance().SetScene("SingleplayerScoreDisplay");
}

void dae::EndGameCommand::GoToEndscreenCoop() {
	auto scene{ std::make_unique<CoopScoreDisplayScene>(m_pScoreComponentP1->GetScore(), m_pScoreComponentP2->GetScore()) };
	SceneManager::GetInstance().AddScene(std::move(scene));
	SceneManager::GetInstance().SetScene("CoopScoreDisplay");
}
