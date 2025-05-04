#include "Qbert.h"
#include "Scene.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "SelectionMenuComponent.h"
#include "LoadSceneCommand.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "RhombilleGridComponent.h"
#include "MenuCommand.h"
#include "SpriteComponent.h"
#include "GridMovementComponent.h"
#include "MoveCommand.h"
#include "hash.h"

dae::Qbert::Qbert() : m_pSoundObserver(std::make_shared<SoundObserver>()) {
	m_pFont = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 30);

	CreateLevelScene();
	CreateMenuScene();

	SceneManager::GetInstance().SetScene(m_pMenuScene); // Set the scene to the menu select scene
}

void dae::Qbert::CreateLevelScene() {
	m_pLevelScene = std::make_shared<Scene>("Level");

	auto mapObject{ std::make_shared<GameObject>(Transform((640 / 2) - 32, 75)) };
	auto rhombileGrid{ mapObject->AddComponent<RhombilleGridComponent>("Qbert Cubes.png", 32, 32, 7, 2.f) };

	auto qbertObject{ std::make_shared<GameObject>() };
	auto qbertSprite{ qbertObject->AddComponent<SpriteComponent>("Qbert P1 Spritesheet.png", 16, 16, 2.f) };
	auto qbertMovementComponent{ qbertObject->AddComponent<GridMovementComponent>(rhombileGrid) };

	qbertSprite->AddState(make_sdbm_hash("right"), SpriteComponent::State{ 1, 1, 1 });
	qbertSprite->SetState(make_sdbm_hash("right"));

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Up, Keyboard::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(qbertMovementComponent, MoveCommand::Direction::Up))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Down, Keyboard::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(qbertMovementComponent, MoveCommand::Direction::Down))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Left, Keyboard::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(qbertMovementComponent, MoveCommand::Direction::Left))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Right, Keyboard::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(qbertMovementComponent, MoveCommand::Direction::Right))
	);

	m_pLevelScene->Add(mapObject);
	m_pLevelScene->Add(qbertObject);
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
