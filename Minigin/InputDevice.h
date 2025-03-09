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
		virtual bool IsConnected() const = 0;

		void BindButton(int button, InputAction action);

		// Unique player identifier (each player gets only 1 device, need to look into this toward future for example
		// keyboard player also could own first controller)
		int GetId() const;

		// Dissalow this type of stuff
		InputDevice(const InputDevice& other) = delete;
		InputDevice(InputDevice&& other) = delete;
		InputDevice& operator=(const InputDevice& other) = delete;
		InputDevice& operator=(InputDevice&& other) = delete;

	protected:
		InputDevice(int id);

		// Actions may not exist
		InputAction* GetAction(int button);

	private:
		std::unordered_map<int, InputAction> m_Bindings;

		// The identifier for this device / player
		int m_id;
	};
}