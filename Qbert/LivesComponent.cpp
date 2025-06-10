#include "LivesComponent.h"
#include "Subject.h"
#include "hash.h"

dae::LivesComponent::LivesComponent(GameObject& pOwner, int maxLives) : BaseComponent(pOwner), m_maxLives(maxLives), m_lives(maxLives) {
}

float dae::LivesComponent::GetPercentage() const {
	return static_cast<float>(m_lives) / static_cast<float>(m_maxLives);
}

int dae::LivesComponent::GetLives() const {
	return m_lives;
}

int dae::LivesComponent::GetMaxLives() const {
	return m_maxLives;
}

void dae::LivesComponent::Kill() {
	m_lives = std::max(0, m_lives - 1);
	m_subject.Notify("killed", m_lives);
}

void dae::LivesComponent::AddLives(int amount) {
	if (amount < 0) {
		return;
	}

	m_lives = std::min(m_maxLives, m_lives + amount);

	Event event{ make_sdbm_hash("lives_added") };
	event.data = std::pair<int, int>(amount, m_lives);
	m_subject.Notify(std::move(event));
}

void dae::LivesComponent::Reset() {
	m_lives = m_maxLives;
}

dae::Subject& dae::LivesComponent::GetSubject() {
	return m_subject;
}
