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
#include "LivesObserver.h"
#include "EnemySpawnerComponent.h"
#include "Qbert.h"

dae::SinglePlayerGameState::SinglePlayerGameState() : AbstractGameState(), m_pScene(std::make_shared<Scene>("Level")) {
	auto mapObject{ std::make_shared<GameObject>(Transform((640 / 2) - 32, 75)) };
	auto rhombileGrid{ mapObject->AddComponent<RhombilleGridComponent>("Qbert Cubes.png", 32, 32, 7, 2.f) };

	auto livesObject{ std::make_shared<GameObject>(Transform{ 10.f, 100.f }) };
	auto livesComponent{ livesObject->AddComponent<LivesComponent>(3) };
	auto repeatingTextureComponent{ livesObject->AddComponent<RepeatingTextureComponent>("Heart.png", 15, 14, 0, 0, 10.f, 2.f)};
	repeatingTextureComponent->SetCols(1); // We only need 1 column value
	repeatingTextureComponent->SetRows(livesComponent->GetLives()); // Set starting value

	// Add the lives observer which will update the repeating texture component
	livesComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(std::make_shared<LivesObserver>(repeatingTextureComponent)));

	auto qbertObject{ std::make_shared<GameObject>() };
	auto qbertSprite{ qbertObject->AddComponent<SpriteComponent>("Qbert P1 Spritesheet.png", 17, 17, 2.f) };
;	m_pPlayerMovementComponent = qbertObject->AddComponent<GridMovementComponent>(rhombileGrid);

	qbertSprite->AddState(make_sdbm_hash("up"), SpriteComponent::State{ 0, 0, 0 });
	qbertSprite->AddState(make_sdbm_hash("down"), SpriteComponent::State{ 3, 0, 0 });
	qbertSprite->AddState(make_sdbm_hash("left"), SpriteComponent::State{ 1, 0, 0 });
	qbertSprite->AddState(make_sdbm_hash("right"), SpriteComponent::State{ 2, 0, 0 });

	qbertSprite->SetState(make_sdbm_hash("right"));

	mapObject->AddComponent<EnemySpawnerComponent>(m_pPlayerMovementComponent, 10.f);

	auto movementObserver{ std::make_shared<PlayerMovementObserver>(qbertSprite, rhombileGrid, livesComponent) };
	m_pPlayerMovementComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(movementObserver));
	m_pPlayerMovementComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(Qbert::GetInstance().GetSoundObserver()));

	m_pScene->Add(livesObject);
	m_pScene->Add(mapObject);
	m_pScene->Add(qbertObject);
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
