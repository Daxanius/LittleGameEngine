#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae {
	class ScoreComponent : public BaseComponent {
	public:
		ScoreComponent(GameObject& pOwner);

		void FixedUpdate() override {};
		void Update(float) override {};
		void PostUpdate() override {};
		void Render() override {};

		void AddToScore(int amount);
		void RemoveFromScore(int amount);

		Subject& GetSubject();

		int GetScore() const;
	private:
		int m_score;

		Subject m_subject;
	};
}

