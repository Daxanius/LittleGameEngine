#include "IntroScene.h"
#include "TextureComponent.h"
#include "ChangeSceneCommand.h"
#include "TimerComponent.h"
#include "TextComponent.h"
#include "SingleplayerLevelScene.h"
#include "SceneManager.h"
#include "ToggleSoundCommand.h"
#include "InputManager.h"
#include "Level.h"
#include "Qbert.h"
#include <iostream>
#include <memory>

dae::IntroScene::IntroScene() : Scene("Intro") {
}

void dae::IntroScene::OnSetup() {
	auto backgroundObject{ std::make_unique<GameObject>() };
	backgroundObject->AddComponent<TextureComponent>("background.jpg");

	m_pTimerComponent = backgroundObject->AddComponent<TimerComponent>();
	m_pTimerComponent->AddCommand(std::make_unique<ChangeSceneCommand>("Menu"));

	auto daeObject{ std::make_unique<GameObject>(Transform((640 / 2) - 100, 180)) };
	daeObject->AddComponent<TextureComponent>("logo.png", 1.f);

	Add(std::move(backgroundObject));
	Add(std::move(daeObject));
}

void dae::IntroScene::OnEnter() {
	InputManager::GetInstance().ClearAllBindings();

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::F2, Keyboard::ActionType::Press },
		std::move(std::make_unique<ToggleSoundCommand>())
	);

	m_pTimerComponent->Start(1.5f);
}
