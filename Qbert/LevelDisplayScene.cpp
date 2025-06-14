#include "LevelDisplayScene.h"
#include "TextureComponent.h"
#include "ChangeSceneCommand.h"
#include "TimerComponent.h"
#include "TextComponent.h"
#include "SingleplayerLevelScene.h"
#include "CoopLevelScene.h"
#include "SceneManager.h"
#include "ToggleSoundCommand.h"
#include "InputManager.h"
#include "Level.h"
#include "Qbert.h"
#include <iostream>
#include <memory>

dae::LevelDisplayScene::LevelDisplayScene(LevelType levelType, int level, int scoreP1, int scoreP2)
	: Scene("LevelDisplay"), m_levelType(levelType), m_level(level), m_scoreP1(scoreP1), m_scoreP2(scoreP2) {
	m_enterSfx = ServiceLocator::GetInstance().GetSoundSystem().RegisterSound("../Data/Sounds/Level Screen Tune.wav");
}

void dae::LevelDisplayScene::OnSetup() {
	const auto& levels{ Qbert::GetInstance().GetLevelInfo() };
	if (m_level >= static_cast<int>(levels.size())) {
		std::cout << "Level does not exist, idiot" << std::endl;
		return;
	}

	Level levelInfo{ levels[m_level] };

	auto levelDisplayObject{ std::make_unique<GameObject>(Transform((640 / 2) - 240, 50)) };
	levelDisplayObject->AddComponent<TextureComponent>(levelInfo.icon);

	m_pTimerComponent = levelDisplayObject->AddComponent<TimerComponent>();
	auto gamemodeTextObject{ std::make_unique<GameObject>(Transform((640 / 2) - 100, 350)) };

	switch (m_levelType) {
		case LevelType::Singleplayer:
			m_pTimerComponent->AddCommand(std::make_unique<ChangeSceneCommand>("SingleplayerLevel"));
			gamemodeTextObject->AddComponent<TextComponent>("Solo Mode", Qbert::GetInstance().GetFontLarge());
			break;
		case LevelType::Coop:
			m_pTimerComponent->AddCommand(std::make_unique<ChangeSceneCommand>("CoopLevel"));
			gamemodeTextObject->AddComponent<TextComponent>("Co-op Mode", Qbert::GetInstance().GetFontLarge());
			break;
	}

	Add(std::move(levelDisplayObject));
	Add(std::move(gamemodeTextObject));
}

void dae::LevelDisplayScene::OnEnter() {
	ServiceLocator::GetInstance().GetSoundSystem().Play(m_enterSfx, 0.2f); // Oopsies, a little rule breaking here :)
	InputManager::GetInstance().ClearAllBindings();

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::F2, Keyboard::ActionType::Press },
		std::move(std::make_unique<ToggleSoundCommand>())
	);

	// Basically reload the level scenes at a new level with a new score
	auto levelScene{ std::make_unique<SingleplayerLevelScene>(m_level, m_scoreP1) };
	SceneManager::GetInstance().AddScene(std::move(levelScene));

	auto levelSceneCoop{ std::make_unique<CoopLevelScene>(m_level, m_scoreP1, m_scoreP2) };
	SceneManager::GetInstance().AddScene(std::move(levelSceneCoop));

	m_pTimerComponent->Start(2.5f);
}