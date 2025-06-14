#include "SingleplayerLevelScene.h"
#include "Transform.h"
#include "RhombilleGridComponent.h"
#include "SpriteComponent.h"
#include "GridMovementComponent.h"
#include "hash.h"
#include "PlayerMovementObserver.h"
#include "LivesComponent.h"
#include "SoundObserver.h"
#include "ChangeSceneCommand.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "MoveCommand.h"
#include "RepeatingTextureComponent.h"
#include "RhombilleGridAnimationComponent.h"
#include "EndGameCommand.h"
#include "PlayerComponent.h"
#include "ChangeToComponent.h"
#include "TimerComponent.h"
#include "PlayerLivesObserver.h"
#include "EnemySpawnerComponent.h"
#include "PauseScene.h"
#include "ParagraphComponent.h"
#include "TextureComponent.h"
#include "ScoreComponent.h"
#include "NextLevelCommand.h"
#include "ScoreObserver.h"
#include "TextComponent.h"
#include "LevelObserver.h"
#include "LevelComponent.h"
#include "SceneManager.h"
#include "ToggleSoundCommand.h"
#include <iostream>
#include "Qbert.h"

dae::SingleplayerLevelScene::SingleplayerLevelScene(int level, int score, bool isVersus) 
	: Scene("SingleplayerLevel"), m_level(level), m_score(score), m_isVersus(isVersus) {
	if (isVersus) {
		SetName("VersusLevel");
	}
}

void dae::SingleplayerLevelScene::OnSetup() {
	const auto& levels{ Qbert::GetInstance().GetLevelInfo() };
	if (m_level >= static_cast<int>(levels.size())) {
		std::cout << "Level does not exist, idiot" << std::endl;
		return;
	}

	m_levelInfo = levels[m_level];

	auto mapObject{ std::make_unique<GameObject>(Transform((640 / 2) - 32, 75, -100.f)) };
	auto pRhombileGridComponent{ mapObject->AddComponent<RhombilleGridComponent>("Qbert Cubes.png", 32, 32, 7, 2.f) };
	mapObject->AddComponent<RhombilleGridAnimationComponent>(2.f, 4);
	auto pLevelComponent{ mapObject->AddComponent<LevelComponent>(2.f, m_levelInfo) };

	auto playerInfoObject(std::make_unique<GameObject>(Transform(10.f, 20.f, 20.f)));
	auto pPlayerInfoSprite{ playerInfoObject->AddComponent<SpriteComponent>("Player Titles.png", 65, 11, 3.f) };

	pPlayerInfoSprite->AddState(make_sdbm_hash("Player1"), SpriteComponent::State{ 0, 0, 1, 0 });
	pPlayerInfoSprite->SetState(make_sdbm_hash("Player1"));

	auto nextTextObject(std::make_unique<GameObject>(Transform(10.f, 106.f, 20.f)));
	nextTextObject->AddComponent<TextComponent>("CHANGE TO", Qbert::GetInstance().GetFontSmall());

	auto nextObject{ std::make_unique<GameObject>(Transform(140.f, 100.f, 20.f) )};
	nextObject->AddComponent<ChangeToComponent>(pLevelComponent, "Color Icons Spritesheet.png", 14, 12, 2.f);

	auto qbertObject{ std::make_unique<GameObject>(Transform{ 0.f, 0.f, 10.f }) };
	m_pPlayerMovementComponent = qbertObject->AddComponent<GridMovementComponent>(pRhombileGridComponent, pLevelComponent);
	auto pLivesComponent{ qbertObject->AddComponent<LivesComponent>(3) };
	auto pQbertSpriteComponent{ qbertObject->AddComponent<SpriteComponent>("Qbert P1 Spritesheet.png", 17, 17, 2.f) };
	m_pScoreComponent = qbertObject->AddComponent<ScoreComponent>(m_score);

	LevelType type{ LevelType::Singleplayer };
	if (m_isVersus) {
		type = LevelType::Versus;
	}

	pLevelComponent->AddNextLevelCommand(std::make_unique<NextLevelCommand>(type, m_level + 1, m_pScoreComponent));

	auto textBalloonObject{ std::make_unique<GameObject>() };
	textBalloonObject->AddComponent<TextureComponent>("Qbert Curses.png", 1.f);
	textBalloonObject->SetParent(qbertObject.get(), false);
	textBalloonObject->SetLocalTransform(Transform(0.f, -30.f));
	textBalloonObject->Disable();

	auto pPlayerComponent{ qbertObject->AddComponent<PlayerComponent>() };
	pPlayerComponent->AddGameOverCommand(std::make_unique<EndGameCommand>(type, m_pScoreComponent));

	// Create a lives display for the player
	auto livesObject{ std::make_unique<GameObject>(Transform{ 10.f, 130.f, 20.f }) };
	auto pRepeatingTexturecomponent{ livesObject->AddComponent<RepeatingTextureComponent>("Heart.png", 15, 14, 0, 0, 10.f, 2.f)};
	pRepeatingTexturecomponent->SetCols(1); // We only need 1 column value

	pRepeatingTexturecomponent->SetRows(pLivesComponent->GetLives()); // Set starting value

	// Add the lives observer which will update the repeating texture component
	pLivesComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(std::make_shared<PlayerLivesObserver>(pRepeatingTexturecomponent, pPlayerComponent, pLevelComponent)));
	pLivesComponent->GetSubject().AddObserver(Qbert::GetInstance().GetSoundObserver());

	pQbertSpriteComponent->AddState(make_sdbm_hash("up"), SpriteComponent::State{ 0, 0, 0, 0 });
	pQbertSpriteComponent->AddState(make_sdbm_hash("down"), SpriteComponent::State{ 3, 0, 0, 0 });
	pQbertSpriteComponent->AddState(make_sdbm_hash("left"), SpriteComponent::State{ 1, 0, 0, 0 });
	pQbertSpriteComponent->AddState(make_sdbm_hash("right"), SpriteComponent::State{ 2, 0, 0, 0 });

	pQbertSpriteComponent->SetState(make_sdbm_hash("right"));

	auto pEnemySpawner{ mapObject->AddComponent<EnemySpawnerComponent>(pLevelComponent, m_isVersus) };

	pLevelComponent->RegisterPlayer(pPlayerComponent);
	pLevelComponent->RegisterSpawner(pEnemySpawner);

	auto movementObserver{ std::make_shared<PlayerMovementObserver>(pPlayerComponent, pLevelComponent) };
	m_pPlayerMovementComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(movementObserver));
	m_pPlayerMovementComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(Qbert::GetInstance().GetSoundObserver()));

	auto scoreObject{ std::make_unique<GameObject>(Transform(10.f, 60.f, 20.f)) };
	auto pScoreTextComponent{ scoreObject->AddComponent<TextComponent>("SCORE:" + std::to_string(m_score), Qbert::GetInstance().GetFontLarge())};

	auto roundObject{ std::make_unique<GameObject>(Transform(420.f, 50.f, 20.f)) };
	auto pRoundTextComponent{ roundObject->AddComponent<TextComponent>("ROUND:1", Qbert::GetInstance().GetFontLarge()) };

	auto levelObject{ std::make_unique<GameObject>(Transform(420.f, 75.f, 20.f)) };
	levelObject->AddComponent<TextComponent>("LEVEL:" + std::to_string(m_level+1), Qbert::GetInstance().GetFontLarge());

	auto scoreObserver{ std::make_shared<ScoreObserver>(pScoreTextComponent) };
	m_pScoreComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(scoreObserver));

	auto levelObserver{ std::make_shared<LevelObserver>(pRoundTextComponent) };
	pLevelComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(levelObserver));
	pLevelComponent->GetSubject().AddObserver(Qbert::GetInstance().GetSoundObserver());

	Add(std::move(livesObject));
	Add(std::move(mapObject));
	Add(std::move(nextTextObject));
	Add(std::move(playerInfoObject));
	Add(std::move(roundObject));
	Add(std::move(levelObject));
	Add(std::move(nextObject));
	Add(std::move(qbertObject));
	Add(std::move(textBalloonObject));
	Add(std::move(scoreObject));
}

void dae::SingleplayerLevelScene::OnEnter() {
	InputManager::GetInstance().ClearAllBindings();

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::F2, Keyboard::ActionType::Press },
		std::move(std::make_unique<ToggleSoundCommand>())
	);

	std::string pauseSceneName{ "SingleplayerLevel" };

	if (m_isVersus) {
		pauseSceneName = "VersusLevel";
	}

	std::unique_ptr<Scene> pauseScene{ std::make_unique<PauseScene>(pauseSceneName)};
	SceneManager::GetInstance().AddScene(std::move(pauseScene));

	if (m_isVersus) {
		InputManager::GetInstance().BindKeyboardCommand(
			Keyboard::KeyState{ Keyboard::Key::F1, Keyboard::ActionType::Press },
			std::move(std::make_unique<NextLevelCommand>(LevelType::Versus,  m_level + 1, m_pScoreComponent))
		);
	} else {
		InputManager::GetInstance().BindKeyboardCommand(
			Keyboard::KeyState{ Keyboard::Key::F1, Keyboard::ActionType::Press },
			std::move(std::make_unique<NextLevelCommand>(LevelType::Singleplayer,  m_level + 1, m_pScoreComponent))
		);
	}

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::W, Keyboard::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pPlayerMovementComponent, MoveCommand::Direction::Up))
	);

	InputManager::GetInstance().BindGamepadCommand(
		0,
		Gamepad::ButtonState{ Gamepad::Button::Up, Gamepad::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pPlayerMovementComponent, MoveCommand::Direction::Up))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::S, Keyboard::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pPlayerMovementComponent, MoveCommand::Direction::Down))
	);

	InputManager::GetInstance().BindGamepadCommand(
		0,
		Gamepad::ButtonState{ Gamepad::Button::Down, Gamepad::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pPlayerMovementComponent, MoveCommand::Direction::Down))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::A, Keyboard::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pPlayerMovementComponent, MoveCommand::Direction::Left))
	);

	InputManager::GetInstance().BindGamepadCommand(
		0,
		Gamepad::ButtonState{ Gamepad::Button::Left, Gamepad::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pPlayerMovementComponent, MoveCommand::Direction::Left))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::D, Keyboard::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pPlayerMovementComponent, MoveCommand::Direction::Right))
	);

	InputManager::GetInstance().BindGamepadCommand(
		0,
		Gamepad::ButtonState{ Gamepad::Button::Right, Gamepad::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pPlayerMovementComponent, MoveCommand::Direction::Right))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Escape, Keyboard::ActionType::Press },
		std::move(std::make_unique<ChangeSceneCommand>("Pause"))
	);

	InputManager::GetInstance().BindGamepadCommand(
		0,
		Gamepad::ButtonState{ Gamepad::Button::Start, Gamepad::ActionType::Press },
		std::move(std::make_unique<ChangeSceneCommand>("Pause"))
	);
}
