#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae {
	class HealthComponent : public BaseComponent {
	public:
		HealthComponent(GameObject& pOwner, int maxHealth);

		// Inherited via BaseComponent
		void FixedUpdate() override {};
		void Update(float) override {};
		void PostUpdate() override {};
		void Render() override {};

		float GetPercentage() const;
		int GetHealth() const;
		int GetMaxHealth() const;

		void Damage(int amount);
		void Heal(int amount);

		void Reset();
	private:
		int m_maxHealth;
		int m_health;

		Subject m_subject;
	};
}
