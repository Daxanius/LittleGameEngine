#include "Gamepad.h"
#include "GamepadXInput.cpp"

dae::Gamepad::~Gamepad() = default;

dae::Gamepad::Gamepad(int playerId, unsigned long controllerId) : InputDevice(playerId), m_pImpl(std::make_unique<Gamepad::impl>(controllerId)) {
	const size_t buttonsToReserve{ static_cast<size_t>(Button::Size) };

	// Reserve all the button states
	m_buttonStates.reserve(buttonsToReserve);

	// Fill states
	for (size_t i{}; i < static_cast<size_t>(Button::Size); i++) {
		m_buttonStates.emplace_back(static_cast<Button>(i), InputActionType::None);
	}
}

void dae::Gamepad::UpdateState() {
	m_pImpl->UpdateState(); // Update the input state (also update connected info)
}

// Process input only gets executed if the device is connected. No need to explicitly check it here.
void dae::Gamepad::ProcessInput() {
	for (size_t i{}; i < static_cast<size_t>(Button::Size); i++) {
		// Get the current button
		const Button button{ static_cast<Button>(i) };

		// Previous state information
		InputActionType& prevState = m_buttonStates[i].actionType;
		const bool wasPressed{ prevState == InputActionType::Hold || prevState == InputActionType::Press };

		// Poll to check of the button is pressed
		const bool isPressedNow{ m_pImpl->PollButton(button) };

		if (isPressedNow) {
			prevState = wasPressed ? InputActionType::Hold : InputActionType::Press;
		} else {
			prevState = wasPressed ? InputActionType::Release : InputActionType::None;
		}

		// Process the button state
		ProcessState(m_buttonStates[i]);
	}
}

void dae::Gamepad::ProcessState(const ButtonState& state) {
	InputAction* action = GetAction(static_cast<int>(state.button));

	// Just continue if the actions do not match or no action was executed
	if (action == nullptr || state.actionType != action->actionType) {
		return;
	}

	// Execute the command if the action matches
	action->command->Execute();
}

bool dae::Gamepad::IsConnected() const {
	return m_pImpl->IsConnected();
}