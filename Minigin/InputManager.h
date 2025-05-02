#pragma once

#include <variant>
#include <unordered_map>
#include <vector>
#include <array>
#include <utility>
#include <functional>

#include "Singleton.h"
#include "Command.h"
#include "Gamepad.h"
#include "Keyboard.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();

		bool ProcessInput();

		void BindKeyboardCommand(const Keyboard::KeyState& state, std::unique_ptr<Command> command);
		void UnbindKeyboardCommand(const Keyboard::KeyState& state);

		void BindGamepadCommand(unsigned int gamepadId, const Gamepad::ButtonState& state, std::unique_ptr<Command> command);
		void UnbindGamepadCommand(unsigned int gamepadId, const Gamepad::ButtonState& state);

		static constexpr int MAX_GAMEPADS = 4;

		InputManager(const InputManager&) = delete;
		InputManager& operator=(const InputManager&) = delete;
		InputManager(InputManager&&) = delete;
		InputManager& operator=(InputManager&&) = delete;
		~InputManager() = default;
	private:
		// The bindings
		std::unordered_map<Keyboard::KeyState, std::unique_ptr<Command>, Keyboard::KeyStateHash> m_keyboardBindings;
		std::array<std::unordered_map<Gamepad::ButtonState, std::unique_ptr<Command>, Gamepad::ButtonStateHash>, MAX_GAMEPADS> m_gamepadBindings;

		// The devices
		std::array<std::unique_ptr<Gamepad>, MAX_GAMEPADS> m_gamepads;
		std::unique_ptr<Keyboard> m_keyboard;
	};
}
