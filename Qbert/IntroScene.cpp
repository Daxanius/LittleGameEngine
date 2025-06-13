#include "IntroScene.h"
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

dae::IntroScrene::IntroScrene() : Scene("Intro") {
}

void dae::IntroScrene::OnSetup() {
	auto backgroundObject{ std::make_unique<GameObject>() };
	backgroundObject->AddComponent<TextureComponent>("background.jpg");

	m_pTimerComponent = backgroundObject->AddComponent<TimerComponent>();
	m_pTimerComponent->AddCommand(std::make_unique<ChangeSceneCommand>("Menu"));

	auto daeObject{ std::make_unique<GameObject>(Transform((640 / 2) - 100, 180)) };
	daeObject->AddComponent<TextureComponent>("logo.png", 1.f);

	Add(std::move(backgroundObject));
	Add(std::move(daeObject));
}

void dae::IntroScrene::OnEnter() {
	m_pTimerComponent->Start(1.5f);
}
