#include "KillCommand.h"
#include <stdexcept>

dae::KillCommand::KillCommand(GameObject* actor, int amount) : ActorCommand(actor), m_amount(amount) {
	m_pHealthComponent = GetActor()->GetComponent<LivesComponent>();
	if (m_pHealthComponent == nullptr) {
		throw std::runtime_error("Actor does not contain health component!");
	}
}

void dae::KillCommand::Execute() {
	m_pHealthComponent->Kill();
}
