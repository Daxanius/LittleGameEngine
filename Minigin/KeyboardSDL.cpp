#pragma once
#include <SDL.h>
#include <optional>

#include "backends/imgui_impl_sdl2.h"

#include "Keyboard.h"

class dae::Keyboard::impl {
public:
	std::optional<InputState> PollEvent() {
		SDL_Event e;

		if (!SDL_PollEvent(&e)) {
			return std::nullopt;
		}

		if (e.type == SDL_KEYDOWN) {

		}

		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}

		// Allow imgui to process the event too. I know, weird to put it here
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	InputActionType MapType(Uint32 eventType) {
		switch (eventType) {
		case SDL_KEYDOWN:
			return InputActionType::Press;
		case SDL_KEYUP:
			return InputActionType::Release;
		default:
			return InputActionType::None;
		}
	}
};