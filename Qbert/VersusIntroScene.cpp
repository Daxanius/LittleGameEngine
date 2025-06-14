#include "VersusIntroScene.h"
#include "Transform.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "ParagraphComponent.h"
#include "InputManager.h"
#include "ToggleSoundCommand.h"
#include "ChangeSceneCommand.h"
#include "SceneManager.h"
#include "LevelDisplayScene.h"
#include "Qbert.h"

dae::VersusIntroScene::VersusIntroScene()
	: Scene("VersusIntro") {
}

void dae::VersusIntroScene::OnSetup() {
	auto titleObject{ std::make_unique<GameObject>(Transform((640 / 2) - 230, 50)) };
	titleObject->AddComponent<TextComponent>("INSTRUCTIONS - VERSUS MODE", Qbert::GetInstance().GetFontMedium());

	auto descriptionObject{ std::make_unique<GameObject>(Transform((640 / 2) - 240, 120)) };
	descriptionObject->AddComponent<ParagraphComponent>(
		"Versus is similar to Solo, but once Coily hatches\n"
		"P2 can take control of it. P2 will win if QBert loses\n"
		"All lives. P1 controls are the same.",
		Qbert::GetInstance().GetFontVerySmall()
	);

	// P1 Controls
	auto p1ControlsImage{ std::make_unique<GameObject>(Transform(50, 250)) };
	p1ControlsImage->AddComponent<TextureComponent>("P2 Coily Controls.png", 0.6f);

	auto orText{ std::make_unique<GameObject>(Transform(260, 300)) };
	orText->AddComponent<TextComponent>("OR", Qbert::GetInstance().GetFontSmall());

	auto p1Gamepad{ std::make_unique<GameObject>(Transform(320, 260)) };
	p1Gamepad->AddComponent<ParagraphComponent>(
		"P1:\n"
		"Move up/right -> DPAD UP\n"
		"Move up/left -> DPAD LEFT\n"
		"Move down/left -> DPAD DOWN\n"
		"Move down/right -> DPAD RIGHT",
		Qbert::GetInstance().GetFontVerySmall()
	);

	auto moveOnPromptObject{ std::make_unique<GameObject>(Transform((640 / 2) - 200, 440)) };
	moveOnPromptObject->AddComponent<TextComponent>("Press ENTER or START to begin the 1st level", Qbert::GetInstance().GetFontVerySmall());

	Add(std::move(titleObject));
	Add(std::move(descriptionObject));
	Add(std::move(p1ControlsImage));
	Add(std::move(orText));
	Add(std::move(p1Gamepad));
	Add(std::move(moveOnPromptObject));
}

void dae::VersusIntroScene::OnEnter() {
	std::unique_ptr<Scene> levelDisplayScene{ std::make_unique<LevelDisplayScene>(LevelType::Versus) };
	SceneManager::GetInstance().AddScene(std::move(levelDisplayScene));

	InputManager::GetInstance().ClearAllBindings();

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::F2, Keyboard::ActionType::Press },
		std::make_unique<ToggleSoundCommand>()
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Enter, Keyboard::ActionType::Press },
		std::make_unique<ChangeSceneCommand>("LevelDisplay")
	);

	InputManager::GetInstance().BindGamepadCommand(
		0,
		Gamepad::ButtonState{ Gamepad::Button::Start, Gamepad::ActionType::Press },
		std::make_unique<ChangeSceneCommand>("LevelDisplay")
	);
}
