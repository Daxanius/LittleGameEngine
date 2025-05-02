#pragma once
#include "Gamepad.h"

#include <windows.h>
#include <Xinput.h>
#include <vector>
#include <cstring>

class dae::Gamepad::impl {
public:
	impl(unsigned long id) : m_id(id) {
		std::memset(&m_state, 0, sizeof(XINPUT_STATE));
		std::memset(&m_prevState, 0, sizeof(XINPUT_STATE));
	}

	void UpdateState() {
		m_buttonStates.clear();

		m_prevState = m_state; // Store previous state
		std::memset(&m_state, 0, sizeof(XINPUT_STATE));

		DWORD result = XInputGetState(m_id, &m_state);
		m_isConnected = result == ERROR_SUCCESS;

		if (!m_isConnected)
			return;

		WORD currentButtons = m_state.Gamepad.wButtons;
		WORD previousButtons = m_prevState.Gamepad.wButtons;

		for (const auto& [bitmask, button] : s_ButtonMappings) {
			bool wasDown = previousButtons & bitmask;
			bool isDown = currentButtons & bitmask;

			ActionType type = ActionType::None;
			if (!wasDown && isDown)
				type = ActionType::Press;
			else if (wasDown && !isDown)
				type = ActionType::Release;
			else if (wasDown && isDown)
				type = ActionType::Hold;

			if (type != ActionType::None) {
				m_buttonStates.emplace_back(ButtonState{ button, type });
			}
		}
	}

	[[nodiscard]] const std::vector<ButtonState>& GetButtonStates() const {
		return m_buttonStates;
	}

	[[nodiscard]] bool IsConnected() const {
		return m_isConnected;
	}

private:
	static constexpr std::pair<WORD, Button> s_ButtonMappings[] = {
			{ static_cast<WORD>(XINPUT_GAMEPAD_START), Button::Start },
			{ static_cast<WORD>(XINPUT_GAMEPAD_BACK), Button::Back },
			{ static_cast<WORD>(XINPUT_GAMEPAD_LEFT_THUMB), Button::LeftThumb },
			{ static_cast<WORD>(XINPUT_GAMEPAD_RIGHT_THUMB), Button::RightThumb },
			{ static_cast<WORD>(XINPUT_GAMEPAD_LEFT_SHOULDER), Button::LeftShoulder },
			{ static_cast<WORD>(XINPUT_GAMEPAD_RIGHT_SHOULDER), Button::RightShoulder },
			{ static_cast<WORD>(XINPUT_GAMEPAD_DPAD_UP), Button::Up },
			{ static_cast<WORD>(XINPUT_GAMEPAD_DPAD_DOWN), Button::Down },
			{ static_cast<WORD>(XINPUT_GAMEPAD_DPAD_LEFT), Button::Left },
			{ static_cast<WORD>(XINPUT_GAMEPAD_DPAD_RIGHT), Button::Right },
			{ static_cast<WORD>(XINPUT_GAMEPAD_A), Button::A },
			{ static_cast<WORD>(XINPUT_GAMEPAD_B), Button::B },
			{ static_cast<WORD>(XINPUT_GAMEPAD_X), Button::X },
			{ static_cast<WORD>(XINPUT_GAMEPAD_Y), Button::Y }
	};

	XINPUT_STATE m_state{};
	XINPUT_STATE m_prevState{};
	DWORD m_id{};
	bool m_isConnected{ true };
	std::vector<ButtonState> m_buttonStates;
};
