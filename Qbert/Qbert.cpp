#include "Qbert.h"
#include "Scene.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "SelectionMenuComponent.h"
#include "LoadSceneCommand.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "MenuCommand.h"

dae::Qbert::Qbert() : m_pSoundObserver(std::make_shared<SoundObserver>()) {
	m_pFont = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 30);

	CreateLevelScene();
	CreateMenuScene();

	SceneManager::GetInstance().SetScene(m_pMenuScene); // Set the scene to the menu select scene
}

void dae::Qbert::CreateLevelScene() {
	m_pLevelScene = std::make_shared<Scene>("Level");
}

void dae::Qbert::CreateMenuScene() {
	m_pMenuScene = std::make_shared<Scene>("Menu");

	auto titleObject{ std::make_shared<GameObject>(Transform((640 / 2) - (474 / 2), 50)) };
	titleObject->AddComponent<TextureComponent>("Game Title.png");

	auto menuObject{ std::make_shared<GameObject>(Transform(640 / 2 - 85, 270)) };
	auto menuComponent{ menuObject->AddComponent<SelectionMenuComponent>(m_pFont, Color{ 252, 203, 43 }, 12, ResourceManager::GetInstance().LoadTexture("Selection Arrow.png"))};

	SelectionMenuComponent::Option optionSolo{ "Solo Mode", std::make_unique<LoadSceneCommand>(m_pLevelScene) };
	menuComponent->AddOption(std::move(optionSolo));

	SelectionMenuComponent::Option optionCoop{ "Co-op Mode", std::make_unique<LoadSceneCommand>(m_pLevelScene) };
	menuComponent->AddOption(std::move(optionCoop));

	SelectionMenuComponent::Option optionVersus{ "Versus Mode", std::make_unique<LoadSceneCommand>(m_pLevelScene) };
	menuComponent->AddOption(std::move(optionVersus));
	menuComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(m_pSoundObserver));

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Up, Keyboard::ActionType::Release },
		std::move(std::make_unique<MenuCommand>(menuComponent, MenuCommand::Action::Previous))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Down, Keyboard::ActionType::Release },
		std::move(std::make_unique<MenuCommand>(menuComponent, MenuCommand::Action::Next))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Enter, Keyboard::ActionType::Release },
		std::move(std::make_unique<MenuCommand>(menuComponent, MenuCommand::Action::Confirm))
	);

	m_pMenuScene->Add(titleObject);
	m_pMenuScene->Add(menuObject);
}
