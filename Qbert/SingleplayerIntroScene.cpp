#include "SingleplayerIntroScene.h"
#include "Transform.h"
#include "RhombilleGridComponent.h"
#include "SpriteComponent.h"
#include "GridMovementComponent.h"
#include "hash.h"
#include "PlayerMovementObserver.h"
#include "LivesComponent.h"
#include "SoundObserver.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "MoveCommand.h"
#include "RepeatingTextureComponent.h"
#include "RhombilleGridAnimationComponent.h"
#include "PlayerComponent.h"
#include "ChangeToComponent.h"
#include "PlayerLivesObserver.h"
#include "EnemySpawnerComponent.h"
#include "ParagraphComponent.h"
#include "TextureComponent.h"
#include "ScoreComponent.h"
#include "TextComponent.h"
#include "LevelComponent.h"
#include "SinglePlayerLevelScene.h"
#include "ToggleSoundCommand.h"
#include "SceneManager.h"
#include "LevelDisplayScene.h"
#include "ChangeSceneCommand.h"
#include "Qbert.h"

dae::SingleplayerIntroScene::SingleplayerIntroScene()
	: Scene("SingleplayerIntro") {
}

void dae::SingleplayerIntroScene::OnSetup() {
	auto instructionsTitleObject{ std::make_unique<GameObject>(Transform((640 / 2) - 220, 50)) };
	instructionsTitleObject->AddComponent<TextComponent>("INSTRUCTIONS - SOLO MODE", Qbert::GetInstance().GetFontMedium());

	auto descriptionObject{ std::make_unique<GameObject>(Transform((640 / 2) - 240, 120)) };
	descriptionObject->AddComponent<ParagraphComponent>(
			"Turn all the cubes of the pyramid in the same color!\n"
			"Step on them to make them change, but be careful\n"
			"to not fall or get hit by enemies while doing so.",
			Qbert::GetInstance().GetFontVerySmall()
	);

	auto wasdObject{ std::make_unique<GameObject>(Transform(50, 250)) };
	wasdObject->AddComponent<TextureComponent>("P1 Controls.png", 0.6f);

	auto orObject{ std::make_unique<GameObject>(Transform(260, 300)) };
	orObject->AddComponent<TextComponent>("OR", Qbert::GetInstance().GetFontSmall());

	auto controlsObject{ std::make_unique<GameObject>(Transform(320, 260)) };
	controlsObject->AddComponent<ParagraphComponent>(
		"Move up/right -> DPAD UP\n"
		"Move up/left -> DPAD LEFT\n"
		"Move down/left -> DPAD DOWN\n"
		"Move down/right -> DPAD RIGHT\n"
		"Pause game -> START",
		Qbert::GetInstance().GetFontVerySmall()
	);

	auto moveOnPromptObject{ std::make_unique<GameObject>(Transform((640 / 2) - 200, 440)) };
	moveOnPromptObject->AddComponent<TextComponent>("Press ENTER or START to begin the 1st level", Qbert::GetInstance().GetFontVerySmall());

	Add(std::move(instructionsTitleObject));
	Add(std::move(descriptionObject));
	Add(std::move(wasdObject));
	Add(std::move(orObject));
	Add(std::move(controlsObject));
	Add(std::move(moveOnPromptObject));
}

void dae::SingleplayerIntroScene::OnEnter() {
	std::unique_ptr<Scene> levelDisplayScene{ std::make_unique<LevelDisplayScene>(LevelType::Singleplayer) };
	SceneManager::GetInstance().AddScene(std::move(levelDisplayScene));

	InputManager::GetInstance().ClearAllBindings();

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::F2, Keyboard::ActionType::Press },
		std::move(std::make_unique<ToggleSoundCommand>())
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Enter, Keyboard::ActionType::Press },
		std::move(std::make_unique<ChangeSceneCommand>("LevelDisplay"))
	);

	InputManager::GetInstance().BindGamepadCommand(
		0,
		Gamepad::ButtonState{ Gamepad::Button::Start, Gamepad::ActionType::Press },
		std::move(std::make_unique<ChangeSceneCommand>("LevelDisplay"))
	);
}
