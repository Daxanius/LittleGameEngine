#pragma once
#include <SDL.h>
#include <optional>
#include <unordered_map>

#include "Keyboard.h"

class dae::Keyboard::impl {
public:
	void Initialize() {
		m_keyboardState = SDL_GetKeyboardState(&m_numKeys);
	}

	void UpdateState() {
		SDL_PumpEvents(); // Update the state of the keyboard for SDL
	}

	bool PollKey(int button) {
		return m_keyboardState[SDL_GetScancodeFromKey(static_cast<SDL_Keycode>(button))];
	}

	int GetKeycount() const {
		return m_numKeys;
	}
private:
	const Uint8* m_keyboardState{ nullptr };
	int m_numKeys{};
};