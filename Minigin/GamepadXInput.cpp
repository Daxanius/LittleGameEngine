#pragma once
#include "Gamepad.h"

#include <windows.h>
#include <Xinput.h> // Xinput used for controller stuffs

class dae::Gamepad::impl {
public:
	dae::Gamepad::impl(unsigned long id) : m_id(id) {
	};

	void UpdateState() {
		std::memset(&m_state, 0, sizeof(XINPUT_STATE));

		// Getting the state 
		DWORD dwResult = XInputGetState(m_id, &m_state);
		m_isConnected = dwResult == ERROR_SUCCESS;
	};


	// Polls to check if a button is pressed
	[[nodiscard]] bool PollButton(Button buttonToPoll) const {
		WORD buttonMask{ m_state.Gamepad.wButtons };

		// Since the switch returns values, breaks are not required
		switch (buttonToPoll) {
			case Button::Start:
				return buttonMask & XINPUT_GAMEPAD_START;
			case Button::Back:
				return buttonMask & XINPUT_GAMEPAD_BACK;
			case Button::Up:
				return buttonMask & XINPUT_GAMEPAD_DPAD_UP;
			case Button::Down:
				return buttonMask & XINPUT_GAMEPAD_DPAD_DOWN;
			case Button::Left:
				return buttonMask & XINPUT_GAMEPAD_DPAD_LEFT;
			case Button::Right:
				return buttonMask & XINPUT_GAMEPAD_DPAD_RIGHT;
			case Button::A:
				return buttonMask & XINPUT_GAMEPAD_A;
			case Button::B:
				return buttonMask & XINPUT_GAMEPAD_B;
			case Button::X:
				return buttonMask & XINPUT_GAMEPAD_X;
			case Button::Y:
				return buttonMask & XINPUT_GAMEPAD_Y;
			case Button::LeftThumb:
				return buttonMask & XINPUT_GAMEPAD_LEFT_THUMB;
			case Button::RightThumb:
				return buttonMask & XINPUT_GAMEPAD_RIGHT_THUMB;
			case Button::LeftShoulder:
				return buttonMask & XINPUT_GAMEPAD_LEFT_SHOULDER;
			case Button::RightShoulder:
				return buttonMask & XINPUT_GAMEPAD_RIGHT_SHOULDER;
			default:
				return false;
		}
	}

	[[nodiscard]] bool IsConnected() const {
		return m_isConnected;
	}

	[[nodiscard]] unsigned int GetId() const {
		return m_id;
	}
private:
	XINPUT_STATE m_state{}; // Gamepad state
	DWORD m_id{};					  // Gamepad id
	bool m_isConnected{ true };
};