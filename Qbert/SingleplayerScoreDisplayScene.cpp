#include "SingleplayerScoreDisplayScene.h"
#include "TextComponent.h"
#include "TextInputCommand.h"
#include "InputManager.h"
#include "Qbert.h"

dae::SingleplayerScoreDisplayScene::SingleplayerScoreDisplayScene() 
	: Scene("SingleplayerScoreDisplay") {
}

void dae::SingleplayerScoreDisplayScene::OnSetup() {
	auto gameOverTextGameObject{ std::make_unique<GameObject>(Transform((640 / 2) - 85, 40)) };
	gameOverTextGameObject->AddComponent<TextComponent>("GAME OVER!", Qbert::GetInstance().GetFontLarge());

	auto scoreInputGameObject{ std::make_unique<GameObject>(Transform((640 / 2) - 40, 120)) };
	m_pTextInputComponent = scoreInputGameObject->AddComponent<TextInputComponent>(4, Qbert::GetInstance().GetFontLarge(), 20);

	Add(std::move(gameOverTextGameObject));
	Add(std::move(scoreInputGameObject));
}

void dae::SingleplayerScoreDisplayScene::OnEnter() {
	InputManager::GetInstance().ClearAllBindings();

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Up, Keyboard::ActionType::Press },
		std::move(std::make_unique<TextInputCommand>(m_pTextInputComponent, TextInputCommand::InputCommand::Up))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Down, Keyboard::ActionType::Press },
		std::move(std::make_unique<TextInputCommand>(m_pTextInputComponent, TextInputCommand::InputCommand::Down))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Left, Keyboard::ActionType::Press },
		std::move(std::make_unique<TextInputCommand>(m_pTextInputComponent, TextInputCommand::InputCommand::Left))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Right, Keyboard::ActionType::Press },
		std::move(std::make_unique<TextInputCommand>(m_pTextInputComponent, TextInputCommand::InputCommand::Right))
	);
}
