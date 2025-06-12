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
#include "LevelDisplayScene.h"
#include "PauseScene.h"
#include "MenuScene.h"
#include "hash.h"

dae::Qbert::Qbert() : m_pSoundObserver(std::make_shared<SoundObserver>()) {
	m_pFontLarge = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 30);
	m_pFontMedium = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 22);
	m_pFontSmall = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 16);

	m_levelInfo = Level::FromFile("../Data/Levels.json");
}

void dae::Qbert::Start() {
	std::unique_ptr<Scene> menuScene{ std::make_unique<MenuScene>() };
	SceneManager::GetInstance().AddScene(std::move(menuScene));

	std::unique_ptr<Scene> introScene{ std::make_unique<SingleplayerIntroScene>() };
	SceneManager::GetInstance().AddScene(std::move(introScene));

	std::unique_ptr<Scene> levelScene{ std::make_unique<SingleplayerLevelScene>() };
	SceneManager::GetInstance().AddScene(std::move(levelScene));

	std::unique_ptr<Scene> levenScene{ std::make_unique<SingleplayerScoreDisplayScene>() };
	SceneManager::GetInstance().AddScene(std::move(levenScene));

	std::unique_ptr<Scene> levelDisplayScene{ std::make_unique<LevelDisplayScene>() };
	SceneManager::GetInstance().AddScene(std::move(levelDisplayScene));

	SceneManager::GetInstance().SetScene("Menu");
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

std::shared_ptr<dae::SoundObserver> dae::Qbert::GetSoundObserver() const {
	return m_pSoundObserver;
}

const std::vector<dae::Level>& dae::Qbert::GetLevelInfo() const {
	return m_levelInfo;
}
