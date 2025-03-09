#pragma once

#include <variant>
#include <unordered_map>
#include <vector>

#include "Singleton.h"
#include "Command.h"
#include "Gamepad.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		// Adds an input device capable of controlling a character to the game.
		// Returns false if it failed (player with given device id probably already exists)
		bool AddInputDevice(std::unique_ptr<InputDevice> device);

		bool ProcessInput();
	private:
		std::vector<std::unique_ptr<InputDevice>> m_players; // Maps player ID to devices
	};
}
