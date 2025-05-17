#pragma once
#include <BaseComponent.h>
#include "GridMovementComponent.h"
#include "Subject.h"

namespace dae {
	class LevelComponent : public BaseComponent {
	public:
		LevelComponent(GameObject& pOwner);

		void NextRound();

		int GetRound() const;
		int GetLevel() const;

		Subject& GetSubject();

		void FixedUpdate() override {};
		void Update(float) override {};
		void PostUpdate() override {};
		void Render() override {};

		static constexpr int ROUNDS_PER_LEVEL{ 4 };
	private:
		// Keeping track of them rounds and levels
		int m_Round{};
		int m_Level{};

		Subject m_Subject{};
	};
}
