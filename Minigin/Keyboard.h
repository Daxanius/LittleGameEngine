#pragma once
#include "InputDevice.h"

namespace dae {
	class Keyboard final : public InputDevice {
	public:
		struct InputState {
			int button;
			InputActionType actionType;
		};

		Keyboard(int playerId);
		~Keyboard();

		void UpdateState() override;
		void ProcessInput() override;
		bool IsConnected() const override;
	private:
		class impl;
		std::unique_ptr<impl> m_pImpl;
	};
}