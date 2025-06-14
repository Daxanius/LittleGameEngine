#include "MenuScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "TextureComponent.h"
#include "SelectionMenuComponent.h"
#include "Font.h"
#include "Observer.h"
#include "hash.h"
#include "SoundObserver.h"
#include "ChangeSceneCommand.h"
#include "ResourceManager.h"
#include "MenuCommand.h"
#include "Qbert.h"
#include "SinglePlayerLevelScene.h"
#include "CoopLevelScene.h"
#include "LevelDisplayScene.h"
#include "ToggleSoundCommand.h"
#include "Scene.h"
#include <memory>

dae::MenuScene::MenuScene() : Scene("Menu") {

}

void dae::MenuScene::OnSetup() {
	auto coopScene{ std::make_unique<CoopLevelScene>(0, 0, 0) };
	SceneManager::GetInstance().AddScene(std::move(coopScene));

	auto titleObject{ std::make_unique<GameObject>(Transform((640 / 2) - (474 / 2), 50)) };
	titleObject->AddComponent<TextureComponent>("Game Title.png");

	auto menuObject{ std::make_unique<GameObject>(Transform(640 / 2 - 120, 270)) };
	m_pSelectionMenuComponent = menuObject->AddComponent<SelectionMenuComponent>(Qbert::GetInstance().GetFontLarge(), Color{252, 203, 43}, 12, ResourceManager::GetInstance().LoadTexture("Selection Arrow.png"));

	SelectionMenuComponent::Option optionSolo{ "Solo Mode", std::make_unique<ChangeSceneCommand>("SingleplayerIntro")};
	m_pSelectionMenuComponent->AddOption(std::move(optionSolo));

	SelectionMenuComponent::Option optionCoop{ "Co-op Mode", std::make_unique<ChangeSceneCommand>("CoopIntro") };
	m_pSelectionMenuComponent->AddOption(std::move(optionCoop));

	SelectionMenuComponent::Option optionVersus{ "Versus Mode", std::make_unique<ChangeSceneCommand>("SingleplayerIntro") };
	m_pSelectionMenuComponent->AddOption(std::move(optionVersus));

	SelectionMenuComponent::Option optionScoreboard{ "Scoreboard", std::make_unique<ChangeSceneCommand>("Scoreboard") };
	m_pSelectionMenuComponent->AddOption(std::move(optionScoreboard));

	m_pSelectionMenuComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(Qbert::GetInstance().GetSoundObserver()));

	Add(std::move(titleObject));
	Add(std::move(menuObject));
}

void dae::MenuScene::OnEnter() {
	// Rebind the input system for the new scene
	InputManager::GetInstance().ClearAllBindings();

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::F2, Keyboard::ActionType::Press },
		std::move(std::make_unique<ToggleSoundCommand>())
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Up, Keyboard::ActionType::Press },
		std::move(std::make_unique<MenuCommand>(m_pSelectionMenuComponent, MenuCommand::Action::Previous))
	);

	InputManager::GetInstance().BindGamepadCommand(
		0,
		Gamepad::ButtonState{ Gamepad::Button::Up, Gamepad::ActionType::Press },
		std::move(std::make_unique<MenuCommand>(m_pSelectionMenuComponent, MenuCommand::Action::Previous))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Down, Keyboard::ActionType::Press },
		std::move(std::make_unique<MenuCommand>(m_pSelectionMenuComponent, MenuCommand::Action::Next))
	);

	InputManager::GetInstance().BindGamepadCommand(
		0,
		Gamepad::ButtonState{ Gamepad::Button::Down, Gamepad::ActionType::Press },
		std::move(std::make_unique<MenuCommand>(m_pSelectionMenuComponent, MenuCommand::Action::Next))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Enter, Keyboard::ActionType::Press },
		std::move(std::make_unique<MenuCommand>(m_pSelectionMenuComponent, MenuCommand::Action::Confirm))
	);

	InputManager::GetInstance().BindGamepadCommand(
		0,
		Gamepad::ButtonState{ Gamepad::Button::A, Gamepad::ActionType::Press },
		std::move(std::make_unique<MenuCommand>(m_pSelectionMenuComponent, MenuCommand::Action::Confirm))
	);

	InputManager::GetInstance().BindGamepadCommand(
		0,
		Gamepad::ButtonState{ Gamepad::Button::Start, Gamepad::ActionType::Press },
		std::move(std::make_unique<MenuCommand>(m_pSelectionMenuComponent, MenuCommand::Action::Confirm))
	);
}
