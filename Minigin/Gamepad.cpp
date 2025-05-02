#include "Gamepad.h"
#include "GamepadXInput.cpp"

dae::Gamepad::~Gamepad() = default;

dae::Gamepad::Gamepad(unsigned long controllerId) : m_pImpl(std::make_unique<Gamepad::impl>(controllerId)) {
}

void dae::Gamepad::UpdateState() {
	m_pImpl->UpdateState(); // Update the input state (also update connected info)
}

const std::vector<dae::Gamepad::ButtonState>& dae::Gamepad::GetButtonStates() const {
	return m_pImpl->GetButtonStates();
}

bool dae::Gamepad::IsConnected() const {
	return m_pImpl->IsConnected();
}