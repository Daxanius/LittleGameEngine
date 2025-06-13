#include "PauseScene.h"
#include "TextureComponent.h"
#include "InputManager.h"
#include "ChangeSceneCommand.h"

dae::PauseScene::PauseScene(const std::string& resumeScene) 
	: Scene("Pause"), m_resumeScene(resumeScene) {
}

void dae::PauseScene::OnSetup() {
	auto backgroundImageObject{ std::make_unique<GameObject>() };
	backgroundImageObject->AddComponent<TextureComponent>("Pause Screen.png");
	Add(std::move(backgroundImageObject));
}

void dae::PauseScene::OnEnter() {
	InputManager::GetInstance().ClearAllBindings();

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Tab, Keyboard::ActionType::Press },
		std::move(std::make_unique<ChangeSceneCommand>(m_resumeScene))
	);

	InputManager::GetInstance().BindGamepadCommand(
		0,
		Gamepad::ButtonState{ Gamepad::Button::Start, Gamepad::ActionType::Press },
		std::move(std::make_unique<ChangeSceneCommand>(m_resumeScene))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Escape, Keyboard::ActionType::Press },
		std::move(std::make_unique<ChangeSceneCommand>("Menu"))
	);

	InputManager::GetInstance().BindGamepadCommand(
		0,
		Gamepad::ButtonState{ Gamepad::Button::Y, Gamepad::ActionType::Release },
		std::move(std::make_unique<ChangeSceneCommand>("Menu"))
	);
}