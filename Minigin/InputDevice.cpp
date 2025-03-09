#include "InputDevice.h"

void dae::InputDevice::Bind(int button, InputAction action) {
	m_Bindings[button] = std::move(action);
}

void dae::InputDevice::Unbind(int button) {
	m_Bindings.erase(button);
}

dae::InputDevice::InputAction* dae::InputDevice::GetAction(int button) {
	auto mapping = m_Bindings.find(button);

	if (mapping == m_Bindings.end()) {
		return nullptr;
	}

	return &mapping->second;
}
