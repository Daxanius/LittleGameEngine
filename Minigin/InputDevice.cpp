#include "InputDevice.h"

void dae::InputDevice::BindButton(int button, InputAction action) {
	m_Bindings[button] = std::move(action);
}

dae::InputDevice::InputAction* dae::InputDevice::GetAction(int button) {
	auto mapping = m_Bindings.find(button);

	if (mapping == m_Bindings.end()) {
		return nullptr;
	}

	return &mapping->second;
}
