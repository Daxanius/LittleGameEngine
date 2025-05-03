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

static void load() {
	auto soundSystemSDL{ std::make_unique<dae::SDLSoundSystem>() };
	auto soundSystemLogging{ std::make_unique<dae::LoggingSoundSystem>(std::move(soundSystemSDL)) };
	dae::ServiceLocator::GetInstance().RegisterSoundSystem(std::move(soundSystemLogging));

	auto& scene = dae::SceneManager::GetInstance().CreateScene("Level");
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);

	return 0;
}