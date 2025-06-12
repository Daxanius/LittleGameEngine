#pragma once
#include <Command.h>
#include "GridMovementComponent.h"

namespace dae {
	class MoveCommand final : public Command {
	public:
		enum class Direction {
			Up,
			Down,
			Left,
			Right
		};

		MoveCommand(GridMovementComponent* movementComponent, Direction direction);

		void Execute() override;
	private:
		// The grid movement component also takes care of animating the transition from one position to the other
		GridMovementComponent* m_pGridMovementComponent;

		Direction m_direction;
	};
}
