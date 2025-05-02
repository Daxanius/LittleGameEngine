#pragma once
#include <SDL.h>
#include <vector>

#include "Keyboard.h"

class dae::Keyboard::impl {
public:
	impl() {
		m_keyboardState = SDL_GetKeyboardState(&m_numKeys);
		m_prevKeyStates.resize(m_numKeys, 0);
	}

	void UpdateState() {
		SDL_PumpEvents(); // Refresh key states
		m_keyStates.clear();

		for (int i = 0; i < m_numKeys; ++i) {
			Uint8 current = m_keyboardState[i];
			Uint8 previous = m_prevKeyStates[i];

			if (current != previous) {
				KeyState ks{};
				ks.key = KeyFromSDLK(SDL_GetKeyFromScancode(static_cast<SDL_Scancode>(i)));

				if (current && !previous) {
					ks.actionType = ActionType::Press;
				}

				else if (!current && previous) {
					 ks.actionType = ActionType::Release;
				} else {
					ks.actionType = ActionType::None;
				}

				if (ks.actionType != ActionType::None) {
					m_keyStates.push_back(ks);
				}
			} else if (current) {
				// Key held
				KeyState ks{};
				ks.key = KeyFromSDLK(SDL_GetKeyFromScancode(static_cast<SDL_Scancode>(i)));
				ks.actionType = ActionType::Hold;
				m_keyStates.push_back(ks);
			}

			m_prevKeyStates[i] = current;
		}
	}

	[[nodiscard]] const std::vector<KeyState>& GetKeyStates() const {
		return m_keyStates;
	}

	[[nodiscard]] bool IsConnected() const {
		return true; // SDL doesn't support keyboard disconnect detection
	}

private:
	// A simple and straightforward key conversion function
	[[nodiscard]] inline Key KeyFromSDLK(SDL_Keycode keycode) {
		switch (keycode) {
			// Letters
			case SDLK_a: return Key::A;
			case SDLK_b: return Key::B;
			case SDLK_c: return Key::C;
			case SDLK_d: return Key::D;
			case SDLK_e: return Key::E;
			case SDLK_f: return Key::F;
			case SDLK_g: return Key::G;
			case SDLK_h: return Key::H;
			case SDLK_i: return Key::I;
			case SDLK_j: return Key::J;
			case SDLK_k: return Key::K;
			case SDLK_l: return Key::L;
			case SDLK_m: return Key::M;
			case SDLK_n: return Key::N;
			case SDLK_o: return Key::O;
			case SDLK_p: return Key::P;
			case SDLK_q: return Key::Q;
			case SDLK_r: return Key::R;
			case SDLK_s: return Key::S;
			case SDLK_t: return Key::T;
			case SDLK_u: return Key::U;
			case SDLK_v: return Key::V;
			case SDLK_w: return Key::W;
			case SDLK_x: return Key::X;
			case SDLK_y: return Key::Y;
			case SDLK_z: return Key::Z;

				// Numbers (top row)
			case SDLK_0: return Key::Num0;
			case SDLK_1: return Key::Num1;
			case SDLK_2: return Key::Num2;
			case SDLK_3: return Key::Num3;
			case SDLK_4: return Key::Num4;
			case SDLK_5: return Key::Num5;
			case SDLK_6: return Key::Num6;
			case SDLK_7: return Key::Num7;
			case SDLK_8: return Key::Num8;
			case SDLK_9: return Key::Num9;

				// Special keys
			case SDLK_SPACE: return Key::Space;
			case SDLK_RETURN: return Key::Enter;
			case SDLK_ESCAPE: return Key::Escape;
			case SDLK_TAB: return Key::Tab;
			case SDLK_BACKSPACE: return Key::Backspace;

				// Arrow keys
			case SDLK_UP: return Key::Up;
			case SDLK_DOWN: return Key::Down;
			case SDLK_LEFT: return Key::Left;
			case SDLK_RIGHT: return Key::Right;

				// Function keys
			case SDLK_F1: return Key::F1;
			case SDLK_F2: return Key::F2;
			case SDLK_F3: return Key::F3;
			case SDLK_F4: return Key::F4;
			case SDLK_F5: return Key::F5;
			case SDLK_F6: return Key::F6;
			case SDLK_F7: return Key::F7;
			case SDLK_F8: return Key::F8;
			case SDLK_F9: return Key::F9;
			case SDLK_F10: return Key::F10;
			case SDLK_F11: return Key::F11;
			case SDLK_F12: return Key::F12;

				// Modifiers
			case SDLK_LSHIFT: return Key::LShift;
			case SDLK_RSHIFT: return Key::RShift;
			case SDLK_LCTRL: return Key::LCtrl;
			case SDLK_RCTRL: return Key::RCtrl;
			case SDLK_LALT: return Key::LAlt;
			case SDLK_RALT: return Key::RAlt;

				// Symbols
			case SDLK_MINUS: return Key::Minus;
			case SDLK_EQUALS: return Key::Equals;
			case SDLK_LEFTBRACKET: return Key::LeftBracket;
			case SDLK_RIGHTBRACKET: return Key::RightBracket;
			case SDLK_SEMICOLON: return Key::Semicolon;
			case SDLK_QUOTE: return Key::Apostrophe;
			case SDLK_COMMA: return Key::Comma;
			case SDLK_PERIOD: return Key::Period;
			case SDLK_SLASH: return Key::Slash;
			case SDLK_BACKSLASH: return Key::Backslash;
			case SDLK_BACKQUOTE: return Key::Grave;
			case SDLK_CAPSLOCK: return Key::CapsLock;

				// Navigation
			case SDLK_INSERT: return Key::Insert;
			case SDLK_DELETE: return Key::Delete;
			case SDLK_HOME: return Key::Home;
			case SDLK_END: return Key::End;
			case SDLK_PAGEUP: return Key::PageUp;
			case SDLK_PAGEDOWN: return Key::PageDown;

			default:
				return Key::Unknown;
		}
	}

	const Uint8* m_keyboardState{ nullptr };
	int m_numKeys{};

	std::vector<Uint8> m_prevKeyStates;
	std::vector<KeyState> m_keyStates;
};
