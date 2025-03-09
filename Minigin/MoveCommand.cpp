#include "MoveCommand.h"

dae::MoveCommand::MoveCommand(GameObject* actor, glm::vec2 direction, float speed) : ActorCommand(actor), m_direction(direction), m_speed(speed) {
}

void dae::MoveCommand::Execute() {
	Transform transform{ GetActor()->GetLocalTransform() };
	const glm::uvec3 position{};
	transform.SetPosition(transform.GetPosition() + glm::vec3(m_direction, 0.0f) * m_speed);
	GetActor()->SetLocalTransform(transform);
}
