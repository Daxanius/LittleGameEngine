#include "LevelComponent.h"
#include "hash.h"

dae::LevelComponent::LevelComponent(GameObject& pOwner) : BaseComponent(pOwner) {
}

void dae::LevelComponent::NextRound() {
	// Go to the next round
	m_Round++;

	// If it's larger or equal to the rounds per level,
	// reset it, go to the next level, and notify the subject
	if (m_Round >= ROUNDS_PER_LEVEL) {
		m_Level++;
		m_Round = 0;
		Event nextLevelEvent{ make_sdbm_hash("next_level") };
		nextLevelEvent.data = m_Level;
		m_Subject.Notify(nextLevelEvent);
		return;
	}

	// Otherwise notify subjects the next round has been triggered
	Event nextRoundEvent{ make_sdbm_hash("next_round") };
	nextRoundEvent.data = m_Round;
	m_Subject.Notify(nextRoundEvent);
}

int dae::LevelComponent::GetRound() const {
	return m_Round;
}

int dae::LevelComponent::GetLevel() const {
	return m_Level;
}

dae::Subject& dae::LevelComponent::GetSubject() {
	return m_Subject;
}