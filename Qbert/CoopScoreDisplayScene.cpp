#include "CoopScoreDisplayScene.h"
#include "GameObject.h"
#include "Transform.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "InputManager.h"
#include "ChangeSceneCommand.h"
#include "ToggleSoundCommand.h"
#include "Qbert.h"

dae::CoopScoreDisplayScene::CoopScoreDisplayScene(int scoreP1, int scoreP2)
	: Scene("CoopScoreDisplay"), m_scoreP1(scoreP1), m_scoreP2(scoreP2) {}

void dae::CoopScoreDisplayScene::OnSetup() {
	auto gameOverTextGameObject{ std::make_unique<GameObject>(Transform((640 / 2) - 180, 20)) };
	gameOverTextGameObject->AddComponent<TextureComponent>("Game Over Title.png");

	auto p1ScoreObject{ std::make_unique<GameObject>(Transform((640 / 2) - 160, 240)) };
	p1ScoreObject->AddComponent<TextComponent>("P1 Score: " + std::to_string(m_scoreP1), Qbert::GetInstance().GetFontLarge());

	auto p2ScoreObject{ std::make_unique<GameObject>(Transform((640 / 2) - 160, 300)) };
	p2ScoreObject->AddComponent<TextComponent>("P2 Score: " + std::to_string(m_scoreP2), Qbert::GetInstance().GetFontLarge());

	auto returnPromptObject{ std::make_unique<GameObject>(Transform((640 / 2) - 180, 440)) };
	returnPromptObject->AddComponent<TextComponent>("Press ENTER or START to return to the menu", Qbert::GetInstance().GetFontVerySmall());

	Add(std::move(gameOverTextGameObject));
	Add(std::move(p1ScoreObject));
	Add(std::move(p2ScoreObject));
	Add(std::move(returnPromptObject));
}

void dae::CoopScoreDisplayScene::OnEnter() {
	InputManager::GetInstance().ClearAllBindings();

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::F2, Keyboard::ActionType::Press },
		std::make_unique<ToggleSoundCommand>()
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Enter, Keyboard::ActionType::Release },
		std::make_unique<ChangeSceneCommand>("Menu")
	);

	InputManager::GetInstance().BindGamepadCommand(
		0,
		Gamepad::ButtonState{ Gamepad::Button::Start, Gamepad::ActionType::Release },
		std::make_unique<ChangeSceneCommand>("Menu")
	);
}
