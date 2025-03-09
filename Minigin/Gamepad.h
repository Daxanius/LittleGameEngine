#pragma once

#include <memory>
#include <variant>
#include <optional>
#include <vector>

#include "InputDevice.h"

namespace dae {
	class Gamepad final : public InputDevice {
	public:
		enum class Button {
			Start,
			Back,
			LeftThumb,
			RightThumb,
			LeftShoulder,
			RightShoulder,
			Up,
			Down,
			Left,
			Right,
			A,
			B,
			X,
			Y,
			Size // Used for looping through the enum values
		};

		struct ButtonState {
			Button button;
			InputActionType actionType;
		};

		Gamepad(unsigned long controllerId);
		~Gamepad();

		void UpdateState() override;
		void ProcessInput() override;

		[[nodiscard]] bool IsConnected() const override;
	private:
		void ProcessState(const ButtonState& state);

		// The gamepad implementation to use
		class impl;
		std::unique_ptr<impl> m_pImpl;

		std::vector<ButtonState> m_buttonStates;
	};
}