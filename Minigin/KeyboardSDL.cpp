#pragma once
#include <SDL.h>

#include "Keyboard.h"

class dae::Keyboard::impl {
public:
	dae::Keyboard::impl() {
		// Initialize the keyboard implementation, SDL has been initialized by the time the game loads.
		m_keyboardState = SDL_GetKeyboardState(&m_numKeys);
	}

	void UpdateState() {
		SDL_PumpEvents(); // Update the state of the keyboard for SDL
	}

	[[nodiscard]] bool PollKey(int button) {
		int scancode = SDL_GetScancodeFromKey(static_cast<SDL_Keycode>(button));
		if (scancode < 0 || scancode >= m_numKeys) return false; // Prevent OOB access
		return m_keyboardState[scancode];
	}

	[[nodiscard]] int GetKeycount() const {
		return m_numKeys;
	}
private:
	const Uint8* m_keyboardState{ nullptr };
	int m_numKeys{};
};