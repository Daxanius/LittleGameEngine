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
		void AddInputDevice(std::unique_ptr<InputDevice> device);

		[[nodiscard]] const std::vector<std::unique_ptr<InputDevice>>& GetDevices() const;

		bool ProcessInput();
	private:
		std::vector<std::unique_ptr<InputDevice>> m_devices;
	};
}
