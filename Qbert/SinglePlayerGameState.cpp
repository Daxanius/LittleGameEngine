#include "SinglePlayerGameState.h"
#include "Transform.h"
#include "RhombilleGridComponent.h"
#include "SpriteComponent.h"
#include "GridMovementComponent.h"
#include "hash.h"
#include "PlayerMovementObserver.h"
#include "LivesComponent.h"
#include "SoundObserver.h"
#include "InputManager.h"
#include "MoveCommand.h"
#include "RepeatingTextureComponent.h"
#include "RhombilleGridAnimationComponent.h"
#include "LivesObserver.h"
#include "EnemySpawnerComponent.h"
#include "ScoreComponent.h"
#include "TextComponent.h"
#include "LevelObserver.h"
#include "LevelComponent.h"
#include "Qbert.h"

dae::SinglePlayerGameState::SinglePlayerGameState() : AbstractGameState(), m_pScene(std::make_shared<Scene>("Level")) {
	auto mapObject{ std::make_shared<GameObject>(Transform((640 / 2) - 32, 75)) };
	auto pRhombileGridComponent{ mapObject->AddComponent<RhombilleGridComponent>("Qbert Cubes.png", 32, 32, 7, 2.f) };
	auto pLevelComponent{ mapObject->AddComponent<LevelComponent>() };
	auto pGridAnimationComponent{ mapObject->AddComponent<RhombilleGridAnimationComponent>(2.f, 4) };

	auto livesObject{ std::make_shared<GameObject>(Transform{ 10.f, 100.f }) };
	auto pLivesComponent{ livesObject->AddComponent<LivesComponent>(3) };
	auto pRepeatingTexturecomponent{ livesObject->AddComponent<RepeatingTextureComponent>("Heart.png", 15, 14, 0, 0, 10.f, 2.f)};
	pRepeatingTexturecomponent->SetCols(1); // We only need 1 column value
	pRepeatingTexturecomponent->SetRows(pLivesComponent->GetLives()); // Set starting value

	// Add the lives observer which will update the repeating texture component
	pLivesComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(std::make_shared<LivesObserver>(pRepeatingTexturecomponent)));

	auto qbertObject{ std::make_shared<GameObject>() };
	auto pQbertSpriteComponent{ qbertObject->AddComponent<SpriteComponent>("Qbert P1 Spritesheet.png", 17, 17, 2.f) };
	auto pScoreComponent{ qbertObject->AddComponent<ScoreComponent>() };
;	m_pPlayerMovementComponent = qbertObject->AddComponent<GridMovementComponent>(pRhombileGridComponent, pLevelComponent);

	pQbertSpriteComponent->AddState(make_sdbm_hash("up"), SpriteComponent::State{ 0, 0, 0 });
	pQbertSpriteComponent->AddState(make_sdbm_hash("down"), SpriteComponent::State{ 3, 0, 0 });
	pQbertSpriteComponent->AddState(make_sdbm_hash("left"), SpriteComponent::State{ 1, 0, 0 });
	pQbertSpriteComponent->AddState(make_sdbm_hash("right"), SpriteComponent::State{ 2, 0, 0 });

	pQbertSpriteComponent->SetState(make_sdbm_hash("right"));

	mapObject->AddComponent<EnemySpawnerComponent>(m_pPlayerMovementComponent, pLevelComponent, 10.f);

	auto movementObserver{ std::make_shared<PlayerMovementObserver>(pQbertSpriteComponent, pRhombileGridComponent, pLivesComponent, pScoreComponent, pLevelComponent, pGridAnimationComponent) };
	m_pPlayerMovementComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(movementObserver));
	m_pPlayerMovementComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(Qbert::GetInstance().GetSoundObserver()));

	auto scoreObject{ std::make_shared<GameObject>(Transform(10.f, 20.f)) };
	auto pScoreTextComponent{ scoreObject->AddComponent<TextComponent>("SCORE: 0",  Qbert::GetInstance().GetFont()) };

	auto levelObserver{ std::make_shared<LevelObserver>(pScoreTextComponent) };
	pScoreComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(levelObserver));
	pLevelComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(levelObserver));

	m_pScene->Add(livesObject);
	m_pScene->Add(mapObject);
	m_pScene->Add(qbertObject);
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
