#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae {
	class LivesComponent : public BaseComponent {
	public:
		LivesComponent(GameObject& pOwner, int maxHealth);

		// Inherited via BaseComponent
		void FixedUpdate() override {};
		void Update(float) override {};
		void PostUpdate() override {};
		void Render() override {};

		float GetPercentage() const;
		int GetLives() const;
		int GetMaxLives() const;

		void Kill();
		void AddLives(int amount);

		void Reset();
	private:
		int m_maxLives;
		int m_lives;

		Subject m_subject{};
	};
}
