#include "CoopLevelScene.h"
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
#include "TextComponent.h"
#include "ScoreObserver.h"
#include "LevelObserver.h"
#include "LevelComponent.h"
#include "SceneManager.h"
#include "ToggleSoundCommand.h"
#include <iostream>
#include "Qbert.h"

dae::CoopLevelScene::CoopLevelScene(int level, int scoreP1, int scoreP2)
	: Scene("CoopLevel"), m_level(level), m_scoreP1(scoreP1), m_scoreP2(scoreP2) {
}

void dae::CoopLevelScene::OnSetup() {
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

	auto playerInfoObjectP1(std::make_unique<GameObject>(Transform(10.f, 20.f, 20.f)));
	auto pPlayerInfoSpriteP1{ playerInfoObjectP1->AddComponent<SpriteComponent>("Player Titles.png", 65, 11, 3.f) };

	pPlayerInfoSpriteP1->AddState(make_sdbm_hash("Player1"), SpriteComponent::State{ 0, 0, 1, 0 });
	pPlayerInfoSpriteP1->SetState(make_sdbm_hash("Player1"));

	auto playerInfoObjectP2(std::make_unique<GameObject>(Transform(400.f, 20.f, 20.f)));
	auto pPlayerInfoSpriteP2{ playerInfoObjectP2->AddComponent<SpriteComponent>("Player Titles.png", 65, 11, 3.f) };

	pPlayerInfoSpriteP2->AddState(make_sdbm_hash("Player2"), SpriteComponent::State{ 0, 1, 1, 0 });
	pPlayerInfoSpriteP2->SetState(make_sdbm_hash("Player2"));

	auto nextTextObject(std::make_unique<GameObject>(Transform(10.f, 90.f, 20.f)));
	nextTextObject->AddComponent<TextComponent>("CHANGE TO", Qbert::GetInstance().GetFontSmall());

	auto nextObject{ std::make_unique<GameObject>(Transform(140.f, 84.f, 20.f) )};
	nextObject->AddComponent<ChangeToComponent>(pLevelComponent, "Color Icons Spritesheet.png", 14, 12, 2.f);

	auto qbertObjectP1{ std::make_unique<GameObject>(Transform{ 0.f, 0.f, 10.f }) };
	m_pPlayer1MovementComponent = qbertObjectP1->AddComponent<GridMovementComponent>(pRhombileGridComponent, pLevelComponent, 6, 0);
	auto pLivesComponentP1{ qbertObjectP1->AddComponent<LivesComponent>(3) };
	auto pQbertSpriteComponentP1{ qbertObjectP1->AddComponent<SpriteComponent>("Qbert P1 Spritesheet.png", 17, 17, 2.f) };
	m_pPlayer1ScoreComponent = qbertObjectP1->AddComponent<ScoreComponent>(m_scoreP1);

	auto qbertObjectP2{ std::make_unique<GameObject>(Transform{ 0.f, 0.f, 10.f }) };
	m_pPlayer2MovementComponent = qbertObjectP2->AddComponent<GridMovementComponent>(pRhombileGridComponent, pLevelComponent, 6, 6);
	auto pLivesComponentP2{ qbertObjectP2->AddComponent<LivesComponent>(3) };
	auto pQbertSpriteComponentP2{ qbertObjectP2->AddComponent<SpriteComponent>("Qbert P2 Spritesheet.png", 17, 17, 2.f) };
	m_pPlayer2ScoreComponent = qbertObjectP2->AddComponent<ScoreComponent>(m_scoreP2);

	pLevelComponent->AddNextLevelCommand(std::make_unique<NextLevelCommand>(LevelType::Coop, m_level + 1, m_pPlayer1ScoreComponent, m_pPlayer2ScoreComponent));

	auto textBalloonObjectP1{ std::make_unique<GameObject>() };
	textBalloonObjectP1->AddComponent<TextureComponent>("Qbert Curses.png", 1.f);
	textBalloonObjectP1->SetParent(qbertObjectP1.get(), false);
	textBalloonObjectP1->SetLocalTransform(Transform(0.f, -30.f));
	textBalloonObjectP1->Disable();

	auto textBalloonObjectP2{ std::make_unique<GameObject>() };
	textBalloonObjectP2->AddComponent<TextureComponent>("Qbert Curses.png", 1.f);
	textBalloonObjectP2->SetParent(qbertObjectP2.get(), false);
	textBalloonObjectP2->SetLocalTransform(Transform(0.f, -30.f));
	textBalloonObjectP2->Disable();

	auto pPlayerComponentP1{ qbertObjectP1->AddComponent<PlayerComponent>() };
	pPlayerComponentP1->AddGameOverCommand(std::make_unique<EndGameCommand>(LevelType::Coop, m_pPlayer1ScoreComponent, m_pPlayer2ScoreComponent));

	auto pPlayerComponentP2{ qbertObjectP2->AddComponent<PlayerComponent>() };
	pPlayerComponentP2->AddGameOverCommand(std::make_unique<EndGameCommand>(LevelType::Coop, m_pPlayer1ScoreComponent, m_pPlayer2ScoreComponent));

	// Create a lives display for the player
	auto livesObjectP1{ std::make_unique<GameObject>(Transform{ 10.f, 130.f, 20.f }) };
	auto pRepeatingTexturecomponentP1{ livesObjectP1->AddComponent<RepeatingTextureComponent>("Heart.png", 15, 14, 0, 0, 10.f, 2.f)};
	pRepeatingTexturecomponentP1->SetCols(1); // We only need 1 column value

	pRepeatingTexturecomponentP1->SetRows(pLivesComponentP1->GetLives()); // Set starting value

	auto livesObjectP2{ std::make_unique<GameObject>(Transform{ 600.f, 130.f, 20.f }) };
	auto pRepeatingTexturecomponentP2{ livesObjectP2->AddComponent<RepeatingTextureComponent>("Heart.png", 15, 14, 0, 0, 10.f, 2.f)};
	pRepeatingTexturecomponentP2->SetCols(1);

	pRepeatingTexturecomponentP2->SetRows(pLivesComponentP2->GetLives());

	// Add the lives observer which will update the repeating texture component
	pLivesComponentP1->GetSubject().AddObserver(std::static_pointer_cast<Observer>(std::make_shared<PlayerLivesObserver>(pRepeatingTexturecomponentP1, pPlayerComponentP1, pLevelComponent)));
	pLivesComponentP1->GetSubject().AddObserver(Qbert::GetInstance().GetSoundObserver());

	pLivesComponentP2->GetSubject().AddObserver(std::static_pointer_cast<Observer>(std::make_shared<PlayerLivesObserver>(pRepeatingTexturecomponentP2, pPlayerComponentP2, pLevelComponent)));
	pLivesComponentP2->GetSubject().AddObserver(Qbert::GetInstance().GetSoundObserver());

	pQbertSpriteComponentP1->AddState(make_sdbm_hash("up"), SpriteComponent::State{ 0, 0, 0, 0 });
	pQbertSpriteComponentP1->AddState(make_sdbm_hash("down"), SpriteComponent::State{ 3, 0, 0, 0 });
	pQbertSpriteComponentP1->AddState(make_sdbm_hash("left"), SpriteComponent::State{ 1, 0, 0, 0 });
	pQbertSpriteComponentP1->AddState(make_sdbm_hash("right"), SpriteComponent::State{ 2, 0, 0, 0 });

	pQbertSpriteComponentP1->SetState(make_sdbm_hash("right"));

	pQbertSpriteComponentP2->AddState(make_sdbm_hash("up"), SpriteComponent::State{ 0, 0, 0, 0 });
	pQbertSpriteComponentP2->AddState(make_sdbm_hash("down"), SpriteComponent::State{ 3, 0, 0, 0 });
	pQbertSpriteComponentP2->AddState(make_sdbm_hash("left"), SpriteComponent::State{ 1, 0, 0, 0 });
	pQbertSpriteComponentP2->AddState(make_sdbm_hash("right"), SpriteComponent::State{ 2, 0, 0, 0 });
												
	pQbertSpriteComponentP2->SetState(make_sdbm_hash("right"));

	auto pEnemySpawner{ mapObject->AddComponent<EnemySpawnerComponent>(pLevelComponent, false) };

	pLevelComponent->RegisterPlayer(pPlayerComponentP1);
	pLevelComponent->RegisterPlayer(pPlayerComponentP2);
	pLevelComponent->RegisterSpawner(pEnemySpawner);

	auto movementObserverP1{ std::make_shared<PlayerMovementObserver>(pPlayerComponentP1, pLevelComponent) };
	m_pPlayer1MovementComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(movementObserverP1));
	m_pPlayer1MovementComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(Qbert::GetInstance().GetSoundObserver()));

	auto movementObserverP2{ std::make_shared<PlayerMovementObserver>(pPlayerComponentP2, pLevelComponent) };
	m_pPlayer2MovementComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(movementObserverP2));
	m_pPlayer2MovementComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(Qbert::GetInstance().GetSoundObserver()));

	auto scoreObjectP1{ std::make_unique<GameObject>(Transform(10.f, 60.f, 20.f)) };
	auto pScoreTextComponentP1{ scoreObjectP1->AddComponent<TextComponent>("SCORE:" + std::to_string(m_scoreP1), Qbert::GetInstance().GetFontMedium()) };

	auto scoreObjectP2{ std::make_unique<GameObject>(Transform(400.f, 60.f, 20.f)) };
	auto pScoreTextComponentP2{ scoreObjectP2->AddComponent<TextComponent>("SCORE:" + std::to_string(m_scoreP2), Qbert::GetInstance().GetFontMedium()) };

	auto roundObject{ std::make_unique<GameObject>(Transform(370, 450.f, 20.f)) };
	auto pRoundTextComponent{ roundObject->AddComponent<TextComponent>("ROUND:1", Qbert::GetInstance().GetFontSmall()) };

	auto levelObject{ std::make_unique<GameObject>(Transform(170, 450.f, 20.f)) };
	levelObject->AddComponent<TextComponent>("LEVEL:" + std::to_string(m_level+1), Qbert::GetInstance().GetFontSmall());

	auto scoreObserverP1{ std::make_shared<ScoreObserver>(pScoreTextComponentP1) };
	m_pPlayer1ScoreComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(scoreObserverP1));

	auto scoreObserverP2{ std::make_shared<ScoreObserver>(pScoreTextComponentP2) };
	m_pPlayer2ScoreComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(scoreObserverP2));

	auto levelObserver{ std::make_shared<LevelObserver>(pRoundTextComponent) };
	pLevelComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(levelObserver));
	pLevelComponent->GetSubject().AddObserver(Qbert::GetInstance().GetSoundObserver());

	Add(std::move(livesObjectP1));
	Add(std::move(livesObjectP2));
	Add(std::move(mapObject));
	Add(std::move(nextTextObject));
	Add(std::move(playerInfoObjectP1));
	Add(std::move(playerInfoObjectP2));
	Add(std::move(roundObject));
	Add(std::move(levelObject));
	Add(std::move(nextObject));
	Add(std::move(qbertObjectP1));
	Add(std::move(qbertObjectP2));
	Add(std::move(textBalloonObjectP1));
	Add(std::move(textBalloonObjectP2));
	Add(std::move(scoreObjectP1));
	Add(std::move(scoreObjectP2));
}

void dae::CoopLevelScene::OnEnter() {
	InputManager::GetInstance().ClearAllBindings();

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::F2, Keyboard::ActionType::Press },
		std::move(std::make_unique<ToggleSoundCommand>())
	);

	std::unique_ptr<Scene> pauseScene{ std::make_unique<PauseScene>("CoopLevel")};
	SceneManager::GetInstance().AddScene(std::move(pauseScene));

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::F1, Keyboard::ActionType::Press },
		std::move(std::make_unique<NextLevelCommand>(LevelType::Coop, m_level + 1, m_pPlayer1ScoreComponent, m_pPlayer2ScoreComponent))
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

	// PLAYER 1
	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::W, Keyboard::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pPlayer1MovementComponent, MoveCommand::Direction::Up))
	);

	InputManager::GetInstance().BindGamepadCommand(
		0,
		Gamepad::ButtonState{ Gamepad::Button::Up, Gamepad::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pPlayer1MovementComponent, MoveCommand::Direction::Up))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::S, Keyboard::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pPlayer1MovementComponent, MoveCommand::Direction::Down))
	);

	InputManager::GetInstance().BindGamepadCommand(
		0,
		Gamepad::ButtonState{ Gamepad::Button::Down, Gamepad::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pPlayer1MovementComponent, MoveCommand::Direction::Down))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::A, Keyboard::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pPlayer1MovementComponent, MoveCommand::Direction::Left))
	);

	InputManager::GetInstance().BindGamepadCommand(
		0,
		Gamepad::ButtonState{ Gamepad::Button::Left, Gamepad::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pPlayer1MovementComponent, MoveCommand::Direction::Left))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::D, Keyboard::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pPlayer1MovementComponent, MoveCommand::Direction::Right))
	);

	InputManager::GetInstance().BindGamepadCommand(
		0,
		Gamepad::ButtonState{ Gamepad::Button::Right, Gamepad::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pPlayer1MovementComponent, MoveCommand::Direction::Right))
	);

	// PLAYER 2
	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Up, Keyboard::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pPlayer2MovementComponent, MoveCommand::Direction::Up))
	);

	InputManager::GetInstance().BindGamepadCommand(
		1,
		Gamepad::ButtonState{ Gamepad::Button::Up, Gamepad::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pPlayer2MovementComponent, MoveCommand::Direction::Up))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Down, Keyboard::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pPlayer2MovementComponent, MoveCommand::Direction::Down))
	);

	InputManager::GetInstance().BindGamepadCommand(
		1,
		Gamepad::ButtonState{ Gamepad::Button::Down, Gamepad::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pPlayer2MovementComponent, MoveCommand::Direction::Down))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Left, Keyboard::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pPlayer2MovementComponent, MoveCommand::Direction::Left))
	);

	InputManager::GetInstance().BindGamepadCommand(
		1,
		Gamepad::ButtonState{ Gamepad::Button::Left, Gamepad::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pPlayer2MovementComponent, MoveCommand::Direction::Left))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Right, Keyboard::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pPlayer2MovementComponent, MoveCommand::Direction::Right))
	);

	InputManager::GetInstance().BindGamepadCommand(
		1,
		Gamepad::ButtonState{ Gamepad::Button::Right, Gamepad::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pPlayer2MovementComponent, MoveCommand::Direction::Right))
	);
}
