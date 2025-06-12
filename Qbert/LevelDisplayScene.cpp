#include "LevelDisplayScene.h"
#include "TextureComponent.h"
#include "ChangeSceneCommand.h"
#include "TimerComponent.h"
#include "TextComponent.h"
#include "Qbert.h"

dae::LevelDisplayScene::LevelDisplayScene()
	: Scene("LevelDisplay") {
}

void dae::LevelDisplayScene::OnSetup() {
	auto levelDisplayObject{ std::make_unique<GameObject>(Transform((640 / 2) - 240, 50)) };

	switch (m_level) {
		case 0:
			levelDisplayObject->AddComponent<TextureComponent>("Level 01 Title.png");
			break;
		case 1:
			levelDisplayObject->AddComponent<TextureComponent>("Level 02 Title.png");
			break;
		case 2:
			levelDisplayObject->AddComponent<TextureComponent>("Level 03 Title.png");
			break;
	}

	m_pTimerComponent = levelDisplayObject->AddComponent<TimerComponent>();
	m_pTimerComponent->AddCommand(std::make_unique<ChangeSceneCommand>("SingleplayerLevel"));

	auto gamemodeTextObject{ std::make_unique<GameObject>(Transform((640 / 2) - 60, 350)) };
	gamemodeTextObject->AddComponent<TextComponent>("Solo Mode", Qbert::GetInstance().GetFontLarge());

	Add(std::move(levelDisplayObject));
	Add(std::move(gamemodeTextObject));
}

void dae::LevelDisplayScene::OnEnter() {
	m_pTimerComponent->Start(2.f);
}