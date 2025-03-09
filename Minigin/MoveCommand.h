#pragma once
#include "Command.h"

namespace dae {
	class MoveCommand final : public ActorCommand {
	public:
		MoveCommand(GameObject* actor, glm::vec2 direction, float speed);

		void Execute() override;
	private:
		glm::vec2 m_direction;
		float m_speed;
	};
}