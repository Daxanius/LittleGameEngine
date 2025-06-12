#include "LevelDisplayScene.h"
#include "TextureComponent.h"
#include "ChangeSceneCommand.h"
#include "TimerComponent.h"
#include "TextComponent.h"
#include "SingleplayerLevelScene.h"
#include "SceneManager.h"
#include "Level.h"
#include "Qbert.h"
#include <iostream>
#include <memory>

dae::LevelDisplayScene::LevelDisplayScene(int level, int score)
	: Scene("LevelDisplay"), m_level(level), m_score(score) {
}

void dae::LevelDisplayScene::OnSetup() {
	// Basically reload the level scene at a new level with a new score
	auto levelScene{ std::make_unique<SingleplayerLevelScene>(m_level, m_score) };
	SceneManager::GetInstance().AddScene(std::move(levelScene));

	const auto& levels{ Qbert::GetInstance().GetLevelInfo() };
	if (m_level >= levels.size()) {
		std::cout << "Level does not exist, idiot" << std::endl;
		return;
	}

	Level levelInfo{ levels[m_level] };

	auto levelDisplayObject{ std::make_unique<GameObject>(Transform((640 / 2) - 240, 50)) };
	levelDisplayObject->AddComponent<TextureComponent>(levelInfo.icon);

	m_pTimerComponent = levelDisplayObject->AddComponent<TimerComponent>();
	m_pTimerComponent->AddCommand(std::make_unique<ChangeSceneCommand>("SingleplayerLevel"));

	auto gamemodeTextObject{ std::make_unique<GameObject>(Transform((640 / 2) - 100, 350)) };
	gamemodeTextObject->AddComponent<TextComponent>("Solo Mode", Qbert::GetInstance().GetFontLarge());

	Add(std::move(levelDisplayObject));
	Add(std::move(gamemodeTextObject));
}

void dae::LevelDisplayScene::OnEnter() {
	m_pTimerComponent->Start(2.f);
}