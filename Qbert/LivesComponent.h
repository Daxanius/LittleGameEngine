#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae {
	class LivesComponent : public BaseComponent {
	public:
		LivesComponent(GameObject& pOwner, int maxLives);

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

		bool IsInvulnerable() const;
		void SetInvulnerable(bool value);

		void Reset();

		Subject& GetSubject();


		LivesComponent(const LivesComponent&) = delete;
		LivesComponent& operator=(const LivesComponent&) = delete;
		LivesComponent(LivesComponent&&) = delete;
		LivesComponent& operator=(LivesComponent&&) = delete;
		~LivesComponent() = default;
	private:
		int m_maxLives;
		int m_lives;

		bool m_invulnerable{};

		Subject m_subject{};
	};
}
