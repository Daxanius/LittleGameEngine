#include "SinglePlayerGameState.h"
#include "Transform.h"
#include "RhombilleGridComponent.h"
#include "SpriteComponent.h"
#include "GridMovementComponent.h"
#include "hash.h"
#include "PlayerMovementObserver.h"
#include "SoundObserver.h"
#include "InputManager.h"
#include "MoveCommand.h"
#include "Qbert.h"

dae::SinglePlayerGameState::SinglePlayerGameState() : AbstractGameState(), m_pScene(std::make_shared<Scene>("Level")) {
	auto mapObject{ std::make_shared<GameObject>(Transform((640 / 2) - 32, 75)) };
	auto rhombileGrid{ mapObject->AddComponent<RhombilleGridComponent>("Qbert Cubes.png", 32, 32, 7, 2.f) };

	auto qbertObject{ std::make_shared<GameObject>() };
	auto qbertSprite{ qbertObject->AddComponent<SpriteComponent>("Qbert P1 Spritesheet.png", 17, 17, 2.f) };
	m_pPlayerMovementComponent = qbertObject->AddComponent<GridMovementComponent>(rhombileGrid);

	qbertSprite->AddState(make_sdbm_hash("up"), SpriteComponent::State{ 0, 0, 0 });
	qbertSprite->AddState(make_sdbm_hash("down"), SpriteComponent::State{ 3, 0, 0 });
	qbertSprite->AddState(make_sdbm_hash("left"), SpriteComponent::State{ 1, 0, 0 });
	qbertSprite->AddState(make_sdbm_hash("right"), SpriteComponent::State{ 2, 0, 0 });

	qbertSprite->SetState(make_sdbm_hash("right"));

	auto movementObserver{ std::make_shared<PlayerMovementObserver>(qbertSprite, rhombileGrid) };
	m_pPlayerMovementComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(movementObserver));
	m_pPlayerMovementComponent->GetSubject().AddObserver(std::static_pointer_cast<Observer>(Qbert::GetInstance().GetSoundObserver()));

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
