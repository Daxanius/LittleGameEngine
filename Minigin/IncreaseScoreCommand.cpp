#include "IncreaseScoreCommand.h"
#include <stdexcept>

dae::IncreaseScoreCommand::IncreaseScoreCommand(GameObject* actor, int amount) : ActorCommand(actor), m_amount(amount) {
	m_pScoreComponent = GetActor()->GetComponent<ScoreComponent>();
	if (m_pScoreComponent == nullptr) {
		throw std::runtime_error("Actor does not contain score component!");
	}
}

void dae::IncreaseScoreCommand::Execute() {
	m_pScoreComponent->AddToScore(m_amount);
}
