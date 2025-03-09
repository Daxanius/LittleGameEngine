#include "InputDevice.h"

void dae::InputDevice::Bind(int button, InputAction action) {
	m_Bindings[button] = std::move(action);
}

dae::InputDevice::InputAction* dae::InputDevice::GetAction(int button) {
	auto mapping = m_Bindings.find(button);

	if (mapping == m_Bindings.end()) {
		return nullptr;
	}

	// If the command has been marked for deletion, remove it 
	// from the bindings and return false.
	if (mapping->second.command->IsUnbound()) {
		Unbind(button);
		return nullptr;
	}

	return &mapping->second;
}

void dae::InputDevice::Unbind(int button) {
	m_Bindings.erase(button);
}