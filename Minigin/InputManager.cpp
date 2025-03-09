#include <SDL.h>
#include "InputManager.h"
#include "backends/imgui_impl_sdl2.h"

bool dae::InputManager::AddInputDevice(std::unique_ptr<InputDevice> device) {
	for (auto& existingDevice : m_players) {
		// Why do I not store these in an unordered map for ids? Latency.
		// Vectors are **blazingly** fast (usually due to cache coherence).
		// Unodered maps have the overhead of hashing ids and looping over them is slower
		// Doing this simple unique check once is more than enough.
		if (existingDevice->GetId() == device->GetId()) {
			return false; // Players with the same device are not allowed to exist
		}
	}

	m_players.emplace_back(std::move(device));
	return true;
}

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}

		if (e.type == SDL_KEYDOWN) {

		}

		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		

		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	// Go through all the devices
	for (auto& device : m_players) {
		device->UpdateState(); // Allow the device to check for reconnections

		if (!device->IsConnected()) {
			continue;
		}

		device->ProcessInput();
	}

	return true;
}