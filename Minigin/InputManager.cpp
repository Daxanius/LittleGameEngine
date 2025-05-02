#include "InputManager.h"

dae::InputManager::InputManager() {
	// Initialize keyboard
	m_keyboard = std::make_unique<Keyboard>();

	// Initialize gamepads (XInput supports up to 4)
	for (unsigned int i = 0; i < MAX_GAMEPADS; ++i) {
		auto gamepad = std::make_unique<Gamepad>(i);
		if (gamepad->IsConnected()) {
			m_gamepads[i] = std::move(gamepad);
		}
	}
}

bool dae::InputManager::ProcessInput() {
	// Update keyboard state
	if (m_keyboard && m_keyboard->IsConnected()) {
		m_keyboard->UpdateState();
		for (const auto& keyState : m_keyboard->GetKeyStates()) {
			auto it = m_keyboardBindings.find(keyState);
			if (it != m_keyboardBindings.end() && it->second) {
				it->second->Execute();
			}
		}
	}

	// Update gamepad states
	for (size_t i = 0; i < MAX_GAMEPADS; ++i) {
		auto& pad = m_gamepads[i];
		if (pad && pad->IsConnected()) {
			pad->UpdateState();
			for (const auto& buttonState : pad->GetButtonStates()) {
				auto it = m_gamepadBindings[i].find(buttonState);
				if (it != m_gamepadBindings[i].end() && it->second) {
					it->second->Execute();
				}
			}
		}
	}

	return true;
}

void dae::InputManager::BindKeyboardCommand(const dae::Keyboard::KeyState& state, std::unique_ptr<dae::Command> command) {
	m_keyboardBindings[state] = std::move(command);
}

void dae::InputManager::UnbindKeyboardCommand(const dae::Keyboard::KeyState& state) {
	m_keyboardBindings.erase(state);
}

void dae::InputManager::BindGamepadCommand(unsigned int gamepadId, const dae::Gamepad::ButtonState& state, std::unique_ptr<dae::Command> command) {
	if (gamepadId >= dae::InputManager::MAX_GAMEPADS) return;
	m_gamepadBindings[gamepadId][state] = std::move(command);
}

void dae::InputManager::UnbindGamepadCommand(unsigned int gamepadId, const dae::Gamepad::ButtonState& state) {
	if (gamepadId >= dae::InputManager::MAX_GAMEPADS) return;
	m_gamepadBindings[gamepadId].erase(state);
}