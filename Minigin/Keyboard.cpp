#include "Keyboard.h"
#include "KeyboardSDL.cpp" // SDL keyboard implementation

// Default deconstructor is sufficient
dae::Keyboard::~Keyboard() = default;

dae::Keyboard::Keyboard() : m_pImpl(std::make_unique<Keyboard::impl>()) {
}

void dae::Keyboard::UpdateState() {
	m_pImpl->UpdateState();
}

const std::vector<dae::Keyboard::KeyState>& dae::Keyboard::GetKeyStates() const {
    return m_pImpl->GetKeyStates();
}

bool dae::Keyboard::IsConnected() const {
	return m_pImpl->IsConnected();
}