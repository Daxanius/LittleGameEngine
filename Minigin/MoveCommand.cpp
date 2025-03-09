#include "MoveCommand.h"
#include <stdexcept>

dae::MoveCommand::MoveCommand(GameObject* actor, glm::vec2 direction) : ActorCommand(actor), m_direction(direction) {
	m_MoveComponent = GetActor()->GetComponent<MoveComponent>();
	if (m_MoveComponent == nullptr) {
		throw std::runtime_error("Actor does not contain move component!");
	}
}

void dae::MoveCommand::Execute() {
	m_MoveComponent->AddDirection(m_direction); // Add our direction to the move component for this frame
}
