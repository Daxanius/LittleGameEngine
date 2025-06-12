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
#include "Scene.h"
#include <memory>

dae::MenuScene::MenuScene() : Scene("Menu") {

}

void dae::MenuScene::OnSetup() {
	auto titleObject{ std::make_unique<GameObject>(Transform((640 / 2) - (474 / 2), 50)) };
	titleObject->AddComponent<TextureComponent>("Game Title.png");

	auto menuObject{ std::make_unique<GameObject>(Transform(640 / 2 - 85, 270)) };
	m_pSelectionMenuComponent = menuObject->AddComponent<SelectionMenuComponent>(Qbert::GetInstance().GetFontLarge(), Color{252, 203, 43}, 12, ResourceManager::GetInstance().LoadTexture("Selection Arrow.png"));

	SelectionMenuComponent::Option optionSolo{ "Solo Mode", std::make_unique<ChangeSceneCommand>("SingleplayerIntro")};
	m_pSelectionMenuComponent->AddOption(std::move(optionSolo));

	SelectionMenuComponent::Option optionCoop{ "Co-op Mode", std::make_unique<ChangeSceneCommand>("SingleplayerIntro") };
	m_pSelectionMenuComponent->AddOption(std::move(optionCoop));

	SelectionMenuComponent::Option optionVersus{ "Versus Mode", std::make_unique<ChangeSceneCommand>("SingleplayerIntro") };

	m_pSelectionMenuComponent->AddOption(std::move(optionVersus));
	m_pSelectionMenuComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(Qbert::GetInstance().GetSoundObserver()));

	Add(std::move(titleObject));
	Add(std::move(menuObject));
}

void dae::MenuScene::OnEnter() {
	// Rebind the input system for the new scene
	InputManager::GetInstance().ClearAllBindings();

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Up, Keyboard::ActionType::Release },
		std::move(std::make_unique<MenuCommand>(m_pSelectionMenuComponent, MenuCommand::Action::Previous))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Down, Keyboard::ActionType::Release },
		std::move(std::make_unique<MenuCommand>(m_pSelectionMenuComponent, MenuCommand::Action::Next))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Enter, Keyboard::ActionType::Release },
		std::move(std::make_unique<MenuCommand>(m_pSelectionMenuComponent, MenuCommand::Action::Confirm))
	);
}
