#include <SDL.h>
#include <iostream>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "ServiceLocator.h"
#include "LoggingSoundSystem.h"
#include "SDLSoundSystem.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "MenuGameState.h"
#include "Qbert.h"

static void load() {
	std::unique_ptr<dae::AbstractSoundSystem> soundSystem = std::make_unique<dae::SDLSoundSystem>();

#ifndef NDEBUG
	soundSystem = std::make_unique<dae::LoggingSoundSystem>(std::move(soundSystem));
#endif

	dae::ServiceLocator::GetInstance().RegisterSoundSystem(std::move(soundSystem));

	// Create the qbert game instance and set the state to be in the menu
	dae::Qbert::GetInstance().SetState(std::make_shared<dae::MenuGameState>());
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);

	return 0;
}