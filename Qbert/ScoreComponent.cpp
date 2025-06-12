#include "ScoreComponent.h"
#include "Subject.h"
#include "hash.h"

dae::ScoreComponent::ScoreComponent(GameObject& pOwner, int pScore) : BaseComponent(pOwner), m_pScore(pScore), m_subject() {
}

void dae::ScoreComponent::AddToScore(int amount) {
	if (amount < 0) {
		return;
	}

	m_pScore += amount;

	Event event{ make_sdbm_hash("score_increased") };
	event.data = std::pair<int, int>(amount, m_pScore);
	m_subject.Notify(std::move(event));
}

void dae::ScoreComponent::RemoveFromScore(int amount) {
	if (amount < 0) {
		return;
	}

	m_pScore = std::max(0, m_pScore - amount);

	Event event{ make_sdbm_hash("score_decreased") };
	event.data = std::pair<int, int>(amount, m_pScore);
	m_subject.Notify(std::move(event));
}

dae::Subject& dae::ScoreComponent::GetSubject() {
	return m_subject;
}

int dae::ScoreComponent::GetScore() const {
	return m_pScore;
}
