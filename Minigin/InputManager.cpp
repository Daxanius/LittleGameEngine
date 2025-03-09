#include <SDL.h>
#include "InputManager.h"
#include "backends/imgui_impl_sdl2.h"

void dae::InputManager::AddInputDevice(std::unique_ptr<InputDevice> device) {
	m_devices.emplace_back(std::move(device));
}

const std::vector<std::unique_ptr<dae::InputDevice>>& dae::InputManager::GetDevices() const {
	return m_devices;
}

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}

		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	// Go through all the devices
	for (auto& device : m_devices) {
		device->UpdateState(); // Allow the device to check for reconnections

		if (!device->IsConnected()) {
			continue;
		}

		device->ProcessInput();
	}

	return true;
}