#include "TimerComponent.h"
#include <utility>

dae::TimerComponent::TimerComponent(GameObject& pOwner) : BaseComponent(pOwner) {
}

void dae::TimerComponent::Start(float time) {
	m_timeLeft = time;
	m_isPaused = false;
}

void dae::TimerComponent::Stop() {
	m_timeLeft = 0.f;
	m_isPaused = true;
}

void dae::TimerComponent::Pause() {
	m_isPaused = true;
}

void dae::TimerComponent::Resume() {
	m_isPaused = false;
}

bool dae::TimerComponent::IsRunning() const {
	return m_isPaused;
}

void dae::TimerComponent::Update(float deltaTime) {
	if (m_isPaused) {
		return;
	}

	if (m_timeLeft <= 0.f) {
		m_isPaused = true;
		m_Subject.Notify("timer_finished");

		for(auto& command : m_commands) {
			command->Execute();
		}
	}

	m_timeLeft -= deltaTime;
}

void dae::TimerComponent::AddCommand(std::unique_ptr<Command>&& command) {
	m_commands.emplace_back(std::forward<std::unique_ptr<Command>>(command));
}
