#include "SinglePlayerGameState.h"
#include "Transform.h"
#include "RhombilleGridComponent.h"
#include "SpriteComponent.h"
#include "GridMovementComponent.h"
#include "hash.h"
#include "PlayerMovementObserver.h"
#include "LivesComponent.h"
#include "SoundObserver.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "MoveCommand.h"
#include "RepeatingTextureComponent.h"
#include "RhombilleGridAnimationComponent.h"
#include "PlayerComponent.h"
#include "ChangeToComponent.h"
#include "PlayerLivesObserver.h"
#include "EnemySpawnerComponent.h"
#include "TextureComponent.h"
#include "ScoreComponent.h"
#include "TextComponent.h"
#include "LevelObserver.h"
#include "LevelComponent.h"
#include "Qbert.h"

dae::SinglePlayerGameState::SinglePlayerGameState() : AbstractGameState(), m_pScene(std::make_shared<Scene>("Level")) {
	auto mapObject{ std::make_shared<GameObject>(Transform((640 / 2) - 32, 75)) };
	auto pRhombileGridComponent{ mapObject->AddComponent<RhombilleGridComponent>("Qbert Cubes.png", 32, 32, 7, 2.f) };
	auto pLevelComponent{ mapObject->AddComponent<LevelComponent>(2.f) };
	auto pGridAnimationComponent{ mapObject->AddComponent<RhombilleGridAnimationComponent>(2.f, 4) };

	auto nextTextObject(std::make_shared<GameObject>(Transform(10.f, 66.f)));
	nextTextObject->AddComponent<TextComponent>("CHANGE TO", dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 16));

	auto nextObject{ std::make_shared<GameObject>(Transform(120.f, 60.f) )};
	nextObject->AddComponent<ChangeToComponent>(pLevelComponent, "Color Icons Spritesheet.png", 14, 12, 2.f);

	auto qbertObject{ std::make_shared<GameObject>() };
	m_pPlayerMovementComponent = qbertObject->AddComponent<GridMovementComponent>(pRhombileGridComponent, pLevelComponent);
	auto pLivesComponent{ qbertObject->AddComponent<LivesComponent>(3) };
	auto pQbertSpriteComponent{ qbertObject->AddComponent<SpriteComponent>("Qbert P1 Spritesheet.png", 17, 17, 2.f) };
	auto pScoreComponent{ qbertObject->AddComponent<ScoreComponent>() };

	auto textBalloonObject{ std::make_shared<GameObject>() };
	textBalloonObject->AddComponent<TextureComponent>("Qbert Curses.png", 1.f);
	textBalloonObject->SetParent(qbertObject.get(), false);
	textBalloonObject->SetLocalTransform(Transform(0.f, -30.f));
	textBalloonObject->Disable();

	auto pPlayerComponent{ qbertObject->AddComponent<PlayerComponent>() };

	// Create a lives display for the player
	auto livesObject{ std::make_shared<GameObject>(Transform{ 10.f, 100.f }) };
	auto pRepeatingTexturecomponent{ livesObject->AddComponent<RepeatingTextureComponent>("Heart.png", 15, 14, 0, 0, 10.f, 2.f)};
	pRepeatingTexturecomponent->SetCols(1); // We only need 1 column value

	pRepeatingTexturecomponent->SetRows(pLivesComponent->GetLives()); // Set starting value

	// Add the lives observer which will update the repeating texture component
	pLivesComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(std::make_shared<PlayerLivesObserver>(pRepeatingTexturecomponent, pPlayerComponent, pLevelComponent)));

	pQbertSpriteComponent->AddState(make_sdbm_hash("up"), SpriteComponent::State{ 0, 0, 0 });
	pQbertSpriteComponent->AddState(make_sdbm_hash("down"), SpriteComponent::State{ 3, 0, 0 });
	pQbertSpriteComponent->AddState(make_sdbm_hash("left"), SpriteComponent::State{ 1, 0, 0 });
	pQbertSpriteComponent->AddState(make_sdbm_hash("right"), SpriteComponent::State{ 2, 0, 0 });

	pQbertSpriteComponent->SetState(make_sdbm_hash("right"));

	auto pEnemySpawner{ mapObject->AddComponent<EnemySpawnerComponent>(m_pPlayerMovementComponent, pLevelComponent, 10.f) };

	pLevelComponent->RegisterPlayer(pPlayerComponent);
	pLevelComponent->RegisterSpawner(pEnemySpawner);

	auto movementObserver{ std::make_shared<PlayerMovementObserver>(pQbertSpriteComponent, pRhombileGridComponent, pLivesComponent, pScoreComponent, pLevelComponent, pGridAnimationComponent) };
	m_pPlayerMovementComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(movementObserver));
	m_pPlayerMovementComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(Qbert::GetInstance().GetSoundObserver()));

	auto scoreObject{ std::make_shared<GameObject>(Transform(10.f, 20.f)) };
	auto pScoreTextComponent{ scoreObject->AddComponent<TextComponent>("SCORE: 0",  Qbert::GetInstance().GetFont()) };

	auto roundObject{ std::make_shared<GameObject>(Transform(420.f, 50.f)) };
	auto pRoundTextComponent{ roundObject->AddComponent<TextComponent>("ROUND: 1",  Qbert::GetInstance().GetFont()) };

	auto levelObject{ std::make_shared<GameObject>(Transform(420.f, 75.f)) };
	auto pLevelTextComponent{ levelObject->AddComponent<TextComponent>("LEVEL: 1",  Qbert::GetInstance().GetFont()) };

	auto levelObserver{ std::make_shared<LevelObserver>(pScoreTextComponent, pRoundTextComponent, pLevelTextComponent) };
	pScoreComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(levelObserver));
	pLevelComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(levelObserver));

	m_pScene->Add(livesObject);
	m_pScene->Add(mapObject);
	m_pScene->Add(nextTextObject);
	m_pScene->Add(roundObject);
	m_pScene->Add(levelObject);
	m_pScene->Add(nextObject);
	m_pScene->Add(qbertObject);
	m_pScene->Add(textBalloonObject);
	m_pScene->Add(scoreObject);
}

void dae::SinglePlayerGameState::OnEnter() {
	InputManager::GetInstance().ClearAllBindings();

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Up, Keyboard::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pPlayerMovementComponent, MoveCommand::Direction::Up))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Down, Keyboard::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pPlayerMovementComponent, MoveCommand::Direction::Down))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Left, Keyboard::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pPlayerMovementComponent, MoveCommand::Direction::Left))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Right, Keyboard::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pPlayerMovementComponent, MoveCommand::Direction::Right))
	);

	SceneManager::GetInstance().SetScene(m_pScene);
}
