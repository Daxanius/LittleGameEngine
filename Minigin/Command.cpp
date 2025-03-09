#include "Command.h"

dae::ActorCommand::ActorCommand(GameObject* actor) : m_Actor(actor) {
	// Let the actor know they are bound to a command, such that actor or command deletion
	// can be handled gracefully
	m_Actor->AddCommandReference(this);
}

dae::GameObject* dae::ActorCommand::GetActor() const {
	return m_Actor;
}

void dae::Command::MarkToUnbind() {
	m_unbound = true;
}

bool dae::Command::IsUnbound() const {
	return m_unbound;
}
