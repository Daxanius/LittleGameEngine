#include "Command.h"

dae::ActorCommand::ActorCommand(GameObject* actor) : m_Actor(actor) {
}

dae::GameObject* dae::ActorCommand::GetActor() const {
	return m_Actor;
}