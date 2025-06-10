#include "MenuGameState.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "TextureComponent.h"
#include "SelectionMenuComponent.h"
#include "Font.h"
#include "Observer.h"
#include "hash.h"
#include "SoundObserver.h"
#include "ChangeGameStateCommand.h"
#include "ResourceManager.h"
#include "MenuCommand.h"
#include "Qbert.h"
#include "SinglePlayerLevelState.h"
#include "SinglePlayerIntroGameState.h"
#include "Scene.h"
#include <memory>

dae::MenuGameState::MenuGameState() : AbstractGameState(), m_pScene(std::make_shared<Scene>("Menu")), m_pSinglePlayerState(std::make_shared<SinglePlayerIntroGameState>()) {
	auto titleObject{ std::make_unique<GameObject>(Transform((640 / 2) - (474 / 2), 50)) };
	titleObject->AddComponent<TextureComponent>("Game Title.png");

	auto menuObject{ std::make_unique<GameObject>(Transform(640 / 2 - 85, 270)) };
	m_pSelectionMenuComponent = menuObject->AddComponent<SelectionMenuComponent>(Qbert::GetInstance().GetFontLarge(), Color{252, 203, 43}, 12, ResourceManager::GetInstance().LoadTexture("Selection Arrow.png"));

	SelectionMenuComponent::Option optionSolo{ "Solo Mode", std::make_unique<ChangeGameStateCommand>(m_pSinglePlayerState) };
	m_pSelectionMenuComponent->AddOption(std::move(optionSolo));

	SelectionMenuComponent::Option optionCoop{ "Co-op Mode", std::make_unique<ChangeGameStateCommand>(m_pSinglePlayerState) };
	m_pSelectionMenuComponent->AddOption(std::move(optionCoop));

	SelectionMenuComponent::Option optionVersus{ "Versus Mode", std::make_unique<ChangeGameStateCommand>(m_pSinglePlayerState) };

	m_pSelectionMenuComponent->AddOption(std::move(optionVersus));
	m_pSelectionMenuComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(Qbert::GetInstance().GetSoundObserver()));

	m_pScene->Add(std::move(titleObject));
	m_pScene->Add(std::move(menuObject));
	SceneManager::GetInstance().AddScene(m_pScene);
}

void dae::MenuGameState::OnEnter() {
	// Rebind the input system for the new scene
	// and load the scene
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

	SceneManager::GetInstance().SetScene(m_pScene);
}
