#include "SingleplayerScoreDisplayScene.h"
#include "TextComponent.h"
#include "TextInputCommand.h"
#include "TextureComponent.h"
#include "InputManager.h"
#include "Qbert.h"

dae::SingleplayerScoreDisplayScene::SingleplayerScoreDisplayScene(int score) 
	: Scene("SingleplayerScoreDisplay"), m_score(score) {
}

void dae::SingleplayerScoreDisplayScene::OnSetup() {
	auto gameOverTextGameObject{ std::make_unique<GameObject>(Transform((640 / 2) - 180, 20)) };
	gameOverTextGameObject->AddComponent<TextureComponent>("Game Over Title.png");

	auto scoreTextGameObject{ std::make_unique<GameObject>(Transform((640 / 2) - 180, 240)) };
	scoreTextGameObject->AddComponent<TextComponent>("Final Score: " + std::to_string(m_score), Qbert::GetInstance().GetFontLarge());

	auto nameInputGameObject{ std::make_unique<GameObject>(Transform((640 / 2) - 40, 300)) };
	m_pTextInputComponent = nameInputGameObject->AddComponent<TextInputComponent>(3, Qbert::GetInstance().GetFontLarge(), 30);

	auto moveOnPromptObject{ std::make_unique<GameObject>(Transform((640 / 2) - 230, 440)) };
	moveOnPromptObject->AddComponent<TextComponent>("Enter name and press START or ENTER to continue", Qbert::GetInstance().GetFontVerySmall());

	Add(std::move(gameOverTextGameObject));
	Add(std::move(scoreTextGameObject));
	Add(std::move(nameInputGameObject));
	Add(std::move(moveOnPromptObject));
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
