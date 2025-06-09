#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae {
	class TimerComponent final : public BaseComponent {
	public:
		TimerComponent(GameObject& pOwner);

		void Start(float time);
		void Stop();

		void Pause();
		void Resume();

		bool IsRunning() const;
		Subject& GetSubject();

		void FixedUpdate() override {};
		void Update(float deltaTime) override;
		void PostUpdate() override {};
		void Render() override {};


		TimerComponent(const TimerComponent&) = delete;
		TimerComponent& operator=(const TimerComponent&) = delete;
		TimerComponent(TimerComponent&&) = delete;
		TimerComponent& operator=(TimerComponent&&) = delete;
		~TimerComponent() = default;

	private:
		float m_timeLeft{};
		bool m_isPaused{ true };

		Subject m_Subject{};
	};
}
