#include "DamageCommand.h"
#include <stdexcept>

dae::DamageCommand::DamageCommand(GameObject* actor, int amount) : ActorCommand(actor), m_amount(amount) {
	m_pHealthComponent = GetActor()->GetComponent<HealthComponent>();
	if (m_pHealthComponent == nullptr) {
		throw std::runtime_error("Actor does not contain health component!");
	}
}

void dae::DamageCommand::Execute() {
	m_pHealthComponent->Damage(m_amount);
}
