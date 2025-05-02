#pragma once
#include <vector>
#include <memory>

namespace dae {
	class Keyboard final {
	public:
		enum class ActionType {
			None,
			Press,
			Hold,
			Release
		};

		enum class Key {
			// Letters
			A, B, C, D, E, F, G, H, I, J,
			K, L, M, N, O, P, Q, R, S, T,
			U, V, W, X, Y, Z,

			// Numbers (top row)
			Num0, Num1, Num2, Num3, Num4,
			Num5, Num6, Num7, Num8, Num9,

			// Numpad
			Numpad0, Numpad1, Numpad2, Numpad3, Numpad4,
			Numpad5, Numpad6, Numpad7, Numpad8, Numpad9,

			// Function keys
			F1, F2, F3, F4, F5, F6,
			F7, F8, F9, F10, F11, F12,

			// Arrows
			Up, Down, Left, Right,

			// Modifiers
			LShift, RShift, LCtrl, RCtrl,
			LAlt, RAlt,

			// Special
			Space, Enter, Escape, Tab, Backspace,

			// Symbols
			Minus, Equals, LeftBracket, RightBracket,
			Semicolon, Apostrophe, Comma, Period,
			Slash, Backslash, Grave, CapsLock,

			// Others
			Insert, Delete, Home, End, PageUp, PageDown, Unknown
		};

		struct KeyState {
			Key key;
			ActionType actionType;
		};

		struct KeyStateHash {
			std::size_t operator()(const KeyState& ks) const {
				std::size_t h1 = std::hash<int>()(static_cast<int>(ks.key));
				std::size_t h2 = std::hash<int>()(static_cast<int>(ks.actionType));
				return h1 ^ (h2 << 1);
			}
		};

		Keyboard();
		~Keyboard();

		void UpdateState();

		// Gets all the keystates of the keyboard
		[[nodiscard]] const std::vector<KeyState>& GetKeyStates() const;

		[[nodiscard]] bool IsConnected() const;
	private:
		class impl;
		std::unique_ptr<impl> m_pImpl;
	};

	inline bool operator==(const Keyboard::KeyState& lhs, const Keyboard::KeyState& rhs) {
		return lhs.key == rhs.key && lhs.actionType == rhs.actionType;
	}
}