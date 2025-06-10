#pragma once
#include "BaseComponent.h"
#include "Subject.h"
#include "Command.h"

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

		void AddCommand(std::unique_ptr<Command>&& command);

		TimerComponent(const TimerComponent&) = delete;
		TimerComponent& operator=(const TimerComponent&) = delete;
		TimerComponent(TimerComponent&&) = delete;
		TimerComponent& operator=(TimerComponent&&) = delete;
		~TimerComponent() = default;

	private:
		float m_timeLeft{};
		bool m_isPaused{ true };

		Subject m_Subject{};

		std::vector<std::unique_ptr<Command>> m_commands;
	};
}
