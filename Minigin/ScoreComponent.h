#pragma once
#include "BaseComponent.h"

namespace dae {
	class ScoreComponent : public BaseComponent {
	public:
		ScoreComponent(GameObject& pOwner);

		// Inherited via BaseComponent
		void FixedUpdate() override {};
		void Update(float) override {};
		void PostUpdate() override {};
		void Render() override {};

		void AddToScore(int amount);
		int GetScore() const;
	private:
		int m_score;
	};
}

