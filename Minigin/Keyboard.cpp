#include "Keyboard.h"
#include "KeyboardSDL.cpp" // SDL keyboard implementation

// Default deconstructor is sufficient
dae::Keyboard::~Keyboard() = default;

dae::Keyboard::Keyboard(int playerId) : InputDevice(playerId) {
}

void dae::Keyboard::UpdateState() {
	
}

void dae::Keyboard::ProcessInput() {
}

bool dae::Keyboard::IsConnected() const {
	// For now, we'll just assume a keyboard is always connected lol, if SDL can make assumptions like this, then so can I
	return true;
}
