#include "Qbert.h"
#include "Scene.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "SelectionMenuComponent.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "RhombilleGridComponent.h"
#include "SpriteComponent.h"
#include "GridMovementComponent.h"
#include "SceneManager.h"
#include "PlayerMovementObserver.h"
#include "MoveCommand.h"
#include "SingleplayerLevelScene.h"
#include "SingleplayerIntroScene.h"
#include "SingleplayerScoreDisplayScene.h"
#include "CoopIntroScene.h"
#include "ScoreboardScene.h"
#include "LevelDisplayScene.h"
#include "IntroScene.h"
#include "PauseScene.h"
#include "MenuScene.h"
#include "hash.h"

dae::Qbert::Qbert() : m_pSoundObserver(std::make_shared<SoundObserver>()) {
	m_pFontLarge = dae::ResourceManager::GetInstance().LoadFont("Zig.ttf", 30);
	m_pFontMedium = dae::ResourceManager::GetInstance().LoadFont("Zig.ttf", 22);
	m_pFontSmall = dae::ResourceManager::GetInstance().LoadFont("Zig.ttf", 16);
	m_pFontVerySmall = dae::ResourceManager::GetInstance().LoadFont("Zig.ttf", 12);

	m_levelInfo = Level::FromFile("../Data/Levels.json");
	m_scoreInfo = Score::FromFile("../Data/Scores.json");
}

void dae::Qbert::Start() {
	std::unique_ptr<Scene> menuScene{ std::make_unique<MenuScene>() };
	SceneManager::GetInstance().AddScene(std::move(menuScene));

	std::unique_ptr<Scene> spIntroScene{ std::make_unique<SingleplayerIntroScene>() };
	SceneManager::GetInstance().AddScene(std::move(spIntroScene));

	std::unique_ptr<Scene> coopIntroScene{ std::make_unique<CoopIntroScene>() };
	SceneManager::GetInstance().AddScene(std::move(coopIntroScene));

	std::unique_ptr<Scene> scoreDisplayScene{ std::make_unique<SingleplayerScoreDisplayScene>() };
	SceneManager::GetInstance().AddScene(std::move(scoreDisplayScene));

	std::unique_ptr<Scene> scoreboardScene{ std::make_unique<ScoreboardScene>(10) };
	SceneManager::GetInstance().AddScene(std::move(scoreboardScene));

	std::unique_ptr<Scene> introScene{ std::make_unique<IntroScene>() };
	SceneManager::GetInstance().AddScene(std::move(introScene));

	SceneManager::GetInstance().SetScene("Intro");
}

std::shared_ptr<dae::Font> dae::Qbert::GetFontLarge() const {
	return m_pFontLarge;
}

std::shared_ptr<dae::Font> dae::Qbert::GetFontMedium() const {
	return m_pFontMedium;
}

std::shared_ptr<dae::Font> dae::Qbert::GetFontSmall() const {
	return m_pFontSmall;
}

std::shared_ptr<dae::Font> dae::Qbert::GetFontVerySmall() const {
	return m_pFontVerySmall;
}

std::shared_ptr<dae::SoundObserver> dae::Qbert::GetSoundObserver() const {
	return m_pSoundObserver;
}

const std::vector<dae::Level>& dae::Qbert::GetLevelInfo() const {
	return m_levelInfo;
}

const std::vector<dae::Score>& dae::Qbert::GetScoreInfo() const {
	return m_scoreInfo;
}

int dae::Qbert::GetLevelCount() const {
	return static_cast<int>(m_levelInfo.size());
}

void dae::Qbert::AddScore(const Score& score) {
	m_scoreInfo.emplace_back(score);
	Score::ToFile(m_scoreInfo, "../Data/Scores.json");
}