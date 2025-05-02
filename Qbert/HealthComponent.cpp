#include "HealthComponent.h"
#include "Subject.h"
#include "hash.h"

dae::HealthComponent::HealthComponent(GameObject& pOwner, int maxHealth) : BaseComponent(pOwner), m_maxHealth(maxHealth), m_health(maxHealth), m_subject() {
}

float dae::HealthComponent::GetPercentage() const {
	return static_cast<float>(m_health) / static_cast<float>(m_maxHealth);
}

int dae::HealthComponent::GetHealth() const {
	return m_health;
}

int dae::HealthComponent::GetMaxHealth() const {
	return m_maxHealth;
}

void dae::HealthComponent::Damage(int amount) {
	if (amount < 0) {
		return;
	}

	m_health = std::max(0, m_health - amount);

	Event event{ make_sdbm_hash("health_decreased") };
	event.data = std::pair<int, int>(amount, m_health);
	m_subject.Notify(event);
}

void dae::HealthComponent::Heal(int amount) {
	if (amount < 0) {
		return;
	}

	m_health = std::min(m_maxHealth, m_health + amount);

	Event event{ make_sdbm_hash("health_increased") };
	event.data = std::pair<int, int>(amount, m_health);
	m_subject.Notify(event);
}

void dae::HealthComponent::Reset() {
	m_health = m_maxHealth;
}
