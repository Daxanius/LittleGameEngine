#include "InputDevice.h"

void dae::InputDevice::BindButton(int button, InputAction action) {
	m_Bindings[button] = std::move(action);
}

int dae::InputDevice::GetId() const {
	return m_id;
}

dae::InputDevice::InputDevice(int id) : m_id(id) {
}

dae::InputDevice::InputAction* dae::InputDevice::GetAction(int button) {
	auto mapping = m_Bindings.find(button);

	if (mapping == m_Bindings.end()) {
		return nullptr;
	}

	return &mapping->second;
}
