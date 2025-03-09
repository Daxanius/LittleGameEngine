#pragma once
#include "InputDevice.h"

namespace dae {
	class Keyboard final : public InputDevice {
	public:
		struct KeyState {
			int key;
			InputActionType actionType;
		};

		Keyboard();
		~Keyboard();

		void UpdateState() override;
		void ProcessInput() override;

		bool IsConnected() const override;
	private:
		void ProcessState(const KeyState& state);

		class impl;
		std::unique_ptr<impl> m_pImpl;

		std::vector<KeyState> m_keyStates;
	};
}