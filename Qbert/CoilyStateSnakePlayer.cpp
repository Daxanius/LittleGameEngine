#include "CoilyStateSnakePlayer.h"
#include "InputManager.h"
#include "MoveCommand.h"

dae::CoilyStateSnakePlayer::CoilyStateSnakePlayer(CoilyComponent* pCoilyComponent)
	: AbstractCoilyState(pCoilyComponent) {
	m_pGridMovementComponent = GetCoilyComponent()->GetComponent<GridMovementComponent>();
	m_pSpriteComponent = GetCoilyComponent()->GetComponent<SpriteComponent>();

	m_pCoilySnakeMovementObserver = std::make_shared<CoilySnakeMovementObserver>(pCoilyComponent);
}

void dae::CoilyStateSnakePlayer::OnEnter() {
	m_pSpriteComponent->SetState(make_sdbm_hash("idle_up"));
	m_pGridMovementComponent->GetSubject().AddObserver(m_pCoilySnakeMovementObserver);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Up, Keyboard::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pGridMovementComponent, MoveCommand::Direction::Up))
	);

	InputManager::GetInstance().BindGamepadCommand(
		1,
		Gamepad::ButtonState{ Gamepad::Button::Up, Gamepad::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pGridMovementComponent, MoveCommand::Direction::Up))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Down, Keyboard::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pGridMovementComponent, MoveCommand::Direction::Down))
	);

	InputManager::GetInstance().BindGamepadCommand(
		1,
		Gamepad::ButtonState{ Gamepad::Button::Down, Gamepad::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pGridMovementComponent, MoveCommand::Direction::Down))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Left, Keyboard::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pGridMovementComponent, MoveCommand::Direction::Left))
	);

	InputManager::GetInstance().BindGamepadCommand(
		1,
		Gamepad::ButtonState{ Gamepad::Button::Left, Gamepad::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pGridMovementComponent, MoveCommand::Direction::Left))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Right, Keyboard::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pGridMovementComponent, MoveCommand::Direction::Right))
	);

	InputManager::GetInstance().BindGamepadCommand(
		1,
		Gamepad::ButtonState{ Gamepad::Button::Right, Gamepad::ActionType::Press },
		std::move(std::make_unique<MoveCommand>(m_pGridMovementComponent, MoveCommand::Direction::Right))
	);
}

void dae::CoilyStateSnakePlayer::Update(float) {
	if (m_pGridMovementComponent->HasArrived()) {
		GetCoilyComponent()->GetSubject().Notify("snake_jump");
	}
}

void dae::CoilyStateSnakePlayer::OnExit() {
	m_pGridMovementComponent->GetSubject().RemoveObserver(m_pCoilySnakeMovementObserver);

	// Unbind all previously bound keyboard commands
	InputManager::GetInstance().UnbindKeyboardCommand(Keyboard::KeyState{ Keyboard::Key::Up, Keyboard::ActionType::Press });
	InputManager::GetInstance().UnbindKeyboardCommand(Keyboard::KeyState{ Keyboard::Key::Down, Keyboard::ActionType::Press });
	InputManager::GetInstance().UnbindKeyboardCommand(Keyboard::KeyState{ Keyboard::Key::Left, Keyboard::ActionType::Press });
	InputManager::GetInstance().UnbindKeyboardCommand(Keyboard::KeyState{ Keyboard::Key::Right, Keyboard::ActionType::Press });

	// Unbind all previously bound gamepad commands
	InputManager::GetInstance().UnbindGamepadCommand(1, Gamepad::ButtonState{ Gamepad::Button::Up, Gamepad::ActionType::Press });
	InputManager::GetInstance().UnbindGamepadCommand(1, Gamepad::ButtonState{ Gamepad::Button::Down, Gamepad::ActionType::Press });
	InputManager::GetInstance().UnbindGamepadCommand(1, Gamepad::ButtonState{ Gamepad::Button::Left, Gamepad::ActionType::Press });
	InputManager::GetInstance().UnbindGamepadCommand(1, Gamepad::ButtonState{ Gamepad::Button::Right, Gamepad::ActionType::Press });
}
