#include "ScoreComponent.h"
#include "Subject.h"
#include "hash.h"

dae::ScoreComponent::ScoreComponent(GameObject& pOwner) : BaseComponent(pOwner), m_score(0) {
}

void dae::ScoreComponent::AddToScore(int amount) {
	if (amount < 0) {
		return;
	}

	m_score += amount;

	Event event{ make_sdbm_hash("score_increased") };
	event.data = std::pair<int, int>(amount, m_score);
	GetOwner().GetSubject()->Notify(event);
}

int dae::ScoreComponent::GetScore() const {
	return m_score;
}
