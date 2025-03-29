#pragma once
#include "Command.h"
#include "MoveComponent.h"

namespace dae {
	class MoveCommand final : public ActorCommand {
	public:
		MoveCommand(GameObject* actor, glm::vec2 direction);

		void Execute() override;
	private:
		glm::vec2 m_direction;

		MoveComponent* m_MoveComponent;
	};
}