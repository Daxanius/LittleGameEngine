#include "Keyboard.h"
#include "KeyboardSDL.cpp" // SDL keyboard implementation

// Default deconstructor is sufficient
dae::Keyboard::~Keyboard() = default;

dae::Keyboard::Keyboard() : InputDevice(), m_pImpl(std::make_unique<Keyboard::impl>()) {
	const int keysToReserve{ m_pImpl->GetKeycount() };

	// Reserve all the button states
	m_keyStates.reserve(keysToReserve);

	// Fill states
	for (int i{}; i < keysToReserve; i++) {
		m_keyStates.emplace_back(i, InputActionType::None);
	}
}

void dae::Keyboard::UpdateState() {
	m_pImpl->UpdateState();
}

void dae::Keyboard::ProcessInput() {
	// Going through all 512 keys is faster than going through the bindings of the hashmap lol.
	for (auto& keyState : m_keyStates) {
		InputActionType& prevState = keyState.actionType;
		const bool wasPressed = (prevState == InputActionType::Hold || prevState == InputActionType::Press);

		const bool isPressedNow = m_pImpl->PollKey(keyState.key);

		prevState = isPressedNow
			? (wasPressed ? InputActionType::Hold : InputActionType::Press)
			: (wasPressed ? InputActionType::Release : InputActionType::None);

		ProcessState(keyState);
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

	// Execute the command if the action matches and a command is bound
	if (action->command) {
		action->command->Execute();
	}
}
