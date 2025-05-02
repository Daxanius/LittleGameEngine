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
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "Scene.h"
#include "FpsComponent.h"
#include "RotatorComponent.h"
#include "InputManager.h"
#include "InputDevice.h"
#include "Gamepad.h"
#include "Keyboard.h"
#include "LogCommand.h"
#include "MoveCommand.h"
#include "PlaySoundCommand.h"
#include "ScoreComponent.h"
#include "Subject.h"
#include "IncreaseScoreCommand.h"
#include "HealthComponent.h"
#include "DamageCommand.h"

static void load() {
	auto soundSystemSDL{ std::make_unique<dae::SDLSoundSystem>() };
	auto soundSystemLogging{ std::make_unique<dae::LoggingSoundSystem>(std::move(soundSystemSDL)) };
	dae::ServiceLocator::GetInstance().RegisterSoundSystem(std::move(soundSystemLogging));

	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	// Create the background object
	auto backgroundObject{ std::make_shared<dae::GameObject>() };
	backgroundObject->AddComponent<dae::TextureComponent>("background.tga");
	scene.Add(backgroundObject);

	// Create the logo object
	auto logoObject{ std::make_shared<dae::GameObject>(std::move(dae::Transform(216.f, 180.f))) };
	logoObject->AddComponent<dae::TextureComponent>("logo.tga");
	scene.Add(logoObject);

	// Create the title object
	auto font{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };

	auto titleObject{ std::make_shared<dae::GameObject>(std::move(dae::Transform(80.f, 20.f))) };
	titleObject->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);
	scene.Add(titleObject);

	// Create the FPS object
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);

	auto fpsObject{ std::make_shared<dae::GameObject>() };
	fpsObject->AddComponent<dae::TextComponent>("FPS", font);
	fpsObject->AddComponent<dae::FpsComponent>();
	scene.Add(fpsObject);

	const float speed{ 100.f };
	const int playerLives{ 3 };

	auto infoObjectP1{ std::make_shared<dae::GameObject>(std::move(dae::Transform(0, 60))) };
	infoObjectP1->AddComponent<dae::TextComponent>("Press E to increase P1 score. Press F to decrease P1 lives.", font);

	auto infoObjectP2{ std::make_shared<dae::GameObject>(std::move(dae::Transform(0, 80))) };
	infoObjectP2->AddComponent<dae::TextComponent>("Press A to increase P2 score. Press B to decrease P2 lives.", font);

	auto player1HealthObject{ std::make_shared<dae::GameObject>(std::move(dae::Transform(0, 100))) };

	auto player1ScoreObject{ std::make_shared<dae::GameObject>(std::move(dae::Transform(0, 130))) }; \

	auto player2HealthObject{ std::make_shared<dae::GameObject>(std::move(dae::Transform(0, 160))) };

	auto player2ScoreObject{ std::make_shared<dae::GameObject>(std::move(dae::Transform(0, 190))) }; \

	scene.Add(infoObjectP1);
	scene.Add(infoObjectP2);
	scene.Add(player1HealthObject);
	scene.Add(player1ScoreObject);
	scene.Add(player2HealthObject);
	scene.Add(player2ScoreObject);

	auto player1{ std::make_shared<dae::GameObject>() };
	player1->AddComponent<dae::TextureComponent>("qbert_char.png");
	player1->AddComponent<dae::MoveComponent>(speed);
	player1->AddComponent<dae::ScoreComponent>();
	player1->AddComponent<dae::HealthComponent>(playerLives);

	// Register observers
	//player1->GetSubject()->AddObserver(std::make_shared<dae::HealthObserver>(player1HealthTextComponent));
	//player1->GetSubject()->AddObserver(std::make_shared<dae::ScoreObserver>(player1ScoreTextComponent));

	// Add player
	scene.Add(player1);

	auto player2{ std::make_shared<dae::GameObject>() };
	player2->AddComponent<dae::TextureComponent>("cool_char.png");
	player2->AddComponent<dae::MoveComponent>(speed * 2);
	player2->AddComponent<dae::ScoreComponent>();
	player2->AddComponent<dae::HealthComponent>(playerLives);

	// Register observers
	//player2->GetSubject()->AddObserver(std::make_shared<dae::HealthObserver>(player2HealthTextComponent));
	//player2->GetSubject()->AddObserver(std::make_shared<dae::ScoreObserver>(player2ScoreTextComponent));

	// Add player
	scene.Add(player2);

	// Keyboard player
	std::unique_ptr<dae::InputDevice> keyboard{ std::make_unique<dae::Keyboard>() };

	// Sound key binding
	keyboard->Bind(
		static_cast<int>(SDLK_SPACE),
		dae::InputDevice::InputAction{
			dae::InputDevice::InputActionType::Release,
			std::move(std::make_unique<dae::PlaySoundCommand>(player1.get(), "../Data/audio/sfx/fx_17a.wav", 1.f))
		});

	keyboard->Bind(
		static_cast<int>(SDLK_a),
		dae::InputDevice::InputAction{
			dae::InputDevice::InputActionType::Hold,
			std::move(std::make_unique<dae::MoveCommand>(player1.get(), glm::vec2(-1, 0)))
		});

	keyboard->Bind(
		static_cast<int>(SDLK_d),
		dae::InputDevice::InputAction{
			dae::InputDevice::InputActionType::Hold,
			std::move(std::make_unique<dae::MoveCommand>(player1.get(), glm::vec2(1, 0)))
		});

	keyboard->Bind(
		static_cast<int>(SDLK_s),
		dae::InputDevice::InputAction{
			dae::InputDevice::InputActionType::Hold,
			std::move(std::make_unique<dae::MoveCommand>(player1.get(), glm::vec2(0, 1)))
		});


	keyboard->Bind(
		static_cast<int>(SDLK_w),
		dae::InputDevice::InputAction{
			dae::InputDevice::InputActionType::Hold,
			std::move(std::make_unique<dae::MoveCommand>(player1.get(), glm::vec2(0, -1)))
		});

	keyboard->Bind(
		static_cast<int>(SDLK_e),
		dae::InputDevice::InputAction{
			dae::InputDevice::InputActionType::Release,
			std::move(std::make_unique<dae::IncreaseScoreCommand>(player1.get(), 100))
		});

	keyboard->Bind(
		static_cast<int>(SDLK_f),
		dae::InputDevice::InputAction{
			dae::InputDevice::InputActionType::Release,
			std::move(std::make_unique<dae::DamageCommand>(player1.get(), 1))
		});

	dae::InputManager::GetInstance().AddInputDevice(std::move(keyboard));

	// Controller player, which is the first connected device (hence 0)
	std::unique_ptr<dae::InputDevice> gamepad{ std::make_unique<dae::Gamepad>(0) };

	gamepad->Bind(
		static_cast<int>(dae::Gamepad::Button::Left),
		dae::InputDevice::InputAction{
			dae::InputDevice::InputActionType::Hold,
			std::move(std::make_unique<dae::MoveCommand>(player2.get(), glm::vec2(-1, 0)))
		});

	gamepad->Bind(
		static_cast<int>(dae::Gamepad::Button::Right),
		dae::InputDevice::InputAction{
			dae::InputDevice::InputActionType::Hold,
			std::move(std::make_unique<dae::MoveCommand>(player2.get(), glm::vec2(1, 0)))
		});

	gamepad->Bind(
		static_cast<int>(dae::Gamepad::Button::Down),
		dae::InputDevice::InputAction{
			dae::InputDevice::InputActionType::Hold,
			std::move(std::make_unique<dae::MoveCommand>(player2.get(), glm::vec2(0, 1)))
		});


	gamepad->Bind(
		static_cast<int>(dae::Gamepad::Button::Up),
		dae::InputDevice::InputAction{
			dae::InputDevice::InputActionType::Hold,
			std::move(std::make_unique<dae::MoveCommand>(player2.get(), glm::vec2(0, -1)))
		});

	gamepad->Bind(
		static_cast<int>(dae::Gamepad::Button::A),
		dae::InputDevice::InputAction{
			dae::InputDevice::InputActionType::Release,
			std::move(std::make_unique<dae::IncreaseScoreCommand>(player2.get(), 100))
		});

	gamepad->Bind(
		static_cast<int>(dae::Gamepad::Button::B),
		dae::InputDevice::InputAction{
			dae::InputDevice::InputActionType::Release,
			std::move(std::make_unique<dae::DamageCommand>(player2.get(), 1))
		});

	dae::InputManager::GetInstance().AddInputDevice(std::move(gamepad));
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);

	return 0;
}