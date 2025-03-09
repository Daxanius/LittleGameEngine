#include "Keyboard.h"
#include "KeyboardSDL.cpp" // SDL keyboard implementation

// Default deconstructor is sufficient
dae::Keyboard::~Keyboard() = default;

dae::Keyboard::Keyboard(int playerId) : InputDevice(playerId) {
	m_pImpl->Initialize(); // Initialize the keyboard implementation, SDL has been initialized by the time the game loads.
}

void dae::Keyboard::UpdateState() {
	m_pImpl->UpdateState();
}

void dae::Keyboard::ProcessInput() {
	for (int i{}; i < m_pImpl->GetKeycount(); i++) {
		// Previous state information
		InputActionType& prevState = m_keyStates[i].actionType;
		const bool wasPressed{ prevState == InputActionType::Hold || prevState == InputActionType::Press };

		// Poll to check of the button is pressed
		const bool isPressedNow{ m_pImpl->PollKey(i) };

		if (isPressedNow) {
			prevState = wasPressed ? InputActionType::Hold : InputActionType::Press;
		} else {
			prevState = wasPressed ? InputActionType::Release : InputActionType::None;
		}

		// Process the key state
		ProcessState(m_keyStates[i]);
	}
}

bool dae::Keyboard::IsConnected() const {
	// For now, we'll just assume a keyboard is always connected lol, if SDL can make assumptions like this, then so can I
	return true;
}

void dae::Keyboard::ProcessState(const KeyState& state) {
	InputAction* action = GetAction(static_cast<int>(state.key));

	// Just continue if the actions do not match or no action was executed
	if (action == nullptr || state.actionType != action->actionType) {
		return;
	}

	// Execute the command if the action matches
	action->command->Execute();
}
