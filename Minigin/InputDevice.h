#pragma once

#include <memory>
#include <unordered_map>

#include "Command.h"

namespace dae {
	// An abstract input device that is easily usable for all devicess
	class InputDevice {
	public:
		enum class InputActionType {
			None,
			Press,
			Hold,
			Release
		};

		struct InputAction {
			InputActionType actionType{};
			std::unique_ptr<Command> command{ nullptr };
		};

		virtual ~InputDevice() = default;

		virtual void UpdateState() = 0;  // Update state allows devices to check if they are still connected and other stuff
		virtual void ProcessInput() = 0; // Only gets executed if the device is marked as connected
		[[nodiscard]] virtual bool IsConnected() const = 0;

		void Bind(int button, InputAction action);

		// Actions may not exist
		InputAction* GetAction(int button);

		// Dissalow this type of stuff
		InputDevice(const InputDevice& other) = delete;
		InputDevice(InputDevice&& other) = delete;
		InputDevice& operator=(const InputDevice& other) = delete;
		InputDevice& operator=(InputDevice&& other) = delete;

	protected:
		InputDevice() = default;

	private:
		// To unbind commands you have to mark the command itself for unbinding (safety reasons, such as when objects refer to commands)
		// One can get bindings using GetAction
		void Unbind(int button);

		std::unordered_map<int, InputAction> m_Bindings;
	};
}