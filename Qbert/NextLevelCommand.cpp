#include "NextLevelCommand.h"
#include "SceneManager.h"
#include "LevelDisplayScene.h"
#include "SingleplayerScoreDisplayScene.h"
#include "CoopScoreDisplayScene.h"
#include "Qbert.h"
#include <memory>

dae::NextLevelCommand::NextLevelCommand(LevelType type, int level, ScoreComponent* pScoreComponentP1, ScoreComponent* pScoreComponentP2)
	: m_levelType(type), m_level(level), m_pScoreComponentP1(pScoreComponentP1), m_pScoreComponentP2(pScoreComponentP2) {
}

void dae::NextLevelCommand::Execute() {
	switch (m_levelType) {
		case LevelType::Singleplayer:
			GoToSinglePlayerLevel();
			break;
		case LevelType::Coop:
			GoToCoopLevel();
			break;
	}
}

void dae::NextLevelCommand::GoToSinglePlayerLevel() {
	if (m_level >= Qbert::GetInstance().GetLevelCount()) {
		auto scene{ std::make_unique<SingleplayerScoreDisplayScene>(m_pScoreComponentP1->GetScore()) };
		SceneManager::GetInstance().AddScene(std::move(scene));
		SceneManager::GetInstance().SetScene("SingleplayerScoreDisplay");
		return;
	}

	auto scene{ std::make_unique<LevelDisplayScene>(m_levelType, m_level, m_pScoreComponentP1->GetScore()) };
	SceneManager::GetInstance().AddScene(std::move(scene));
	SceneManager::GetInstance().SetScene("LevelDisplay");
}

void dae::NextLevelCommand::GoToCoopLevel() {
	if (m_level >= Qbert::GetInstance().GetLevelCount()) {
		auto scene{ std::make_unique<CoopScoreDisplayScene>(m_pScoreComponentP1->GetScore(), m_pScoreComponentP2->GetScore()) };
		SceneManager::GetInstance().AddScene(std::move(scene));
		SceneManager::GetInstance().SetScene("CoopScoreDisplay");
		return;
	}

	auto scene{ std::make_unique<LevelDisplayScene>(m_levelType, m_level, m_pScoreComponentP1->GetScore(), m_pScoreComponentP2->GetScore()) };
	SceneManager::GetInstance().AddScene(std::move(scene));
	SceneManager::GetInstance().SetScene("LevelDisplay");
}
