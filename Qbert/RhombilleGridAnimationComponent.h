#pragma once
#include <BaseComponent.h>
#include "RhombilleGridComponent.h"
#include "Subject.h"

namespace dae {
	class RhombilleGridAnimationComponent final : public BaseComponent {
	public:
		RhombilleGridAnimationComponent(GameObject& pOwner, float animationDuration, int repetitions = 2);

		void FixedUpdate() override {};
		void Update(float deltaTime) override;
		void PostUpdate() override {};
		void Render() override {};

		Subject& GetSubject();

		void PlayAnimation();

		bool IsPlaying() const;


		RhombilleGridAnimationComponent(const RhombilleGridAnimationComponent&) = delete;
		RhombilleGridAnimationComponent& operator=(const RhombilleGridAnimationComponent&) = delete;
		RhombilleGridAnimationComponent(RhombilleGridAnimationComponent&&) = delete;
		RhombilleGridAnimationComponent& operator=(RhombilleGridAnimationComponent&&) = delete;
		~RhombilleGridAnimationComponent() = default;
	private:
		RhombilleGridComponent* m_pRhombilleGridComponent{};

		float m_animationDuration;

		int m_originalState{};
		int m_repetitions{};
		int m_currentState{};
		float m_currentTimeLeft{};

		bool m_playing{};

		Subject m_Subject{};
	};
}
