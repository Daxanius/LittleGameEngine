#include "MoveCommand.h"

dae::MoveCommand::MoveCommand(GridMovementComponent* movementComponent, Direction direction) : m_pGridMovementComponent(movementComponent), m_direction(direction) {
}

void dae::MoveCommand::Execute() {
	switch (m_direction) {
		case Direction::Up:
			m_pGridMovementComponent->MoveUp();
			break;
		case Direction::Down:
			m_pGridMovementComponent->MoveDown();
			break;
		case Direction::Left:
			m_pGridMovementComponent->MoveLeft();
			break;
		case Direction::Right:
			m_pGridMovementComponent->MoveRight();
			break;
	}
}
