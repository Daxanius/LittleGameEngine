#include "SinglePlayerIntroGameState.h"
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
#include "PauseCommand.h"
#include "PlayerComponent.h"
#include "ChangeToComponent.h"
#include "PlayerLivesObserver.h"
#include "EnemySpawnerComponent.h"
#include "ParagraphComponent.h"
#include "TextureComponent.h"
#include "ScoreComponent.h"
#include "TextComponent.h"
#include "LevelObserver.h"
#include "LevelComponent.h"
#include "SinglePlayerGameState.h"
#include "ChangeGameStateCommand.h"
#include "Qbert.h"

dae::SinglePlayerIntroGameState::SinglePlayerIntroGameState()
	: AbstractGameState(), m_pTutorialScene(std::make_shared<Scene>("Tutorial")), m_pSinglePlayerState(std::make_shared<SinglePlayerGameState>()) {
		auto instructionsTitleObject{ std::make_unique<GameObject>(Transform((640 / 2) - 220, 50)) };
	instructionsTitleObject->AddComponent<TextComponent>("INSTRUCTIONS - SOLO MODE", Qbert::GetInstance().GetFontLarge());

	auto descriptionObject{ std::make_unique<GameObject>(Transform((640 / 2) - 200, 120)) };
	descriptionObject->AddComponent<ParagraphComponent>(
			"Turn all the cubes of the pyramid in the same color!\n"
			"Step on them to make them change, but be careful\n"
			"to not fall or get hit by enemies while doing so.",
			Qbert::GetInstance().GetFontSmall()
	);

	auto wasdObject{ std::make_unique<GameObject>(Transform(50, 250)) };
	wasdObject->AddComponent<TextureComponent>("P1 Controls.png", 0.6f);

	auto orObject{ std::make_unique<GameObject>(Transform(280, 300)) };
	orObject->AddComponent<TextComponent>("OR", Qbert::GetInstance().GetFontSmall());

	auto controlsObject{ std::make_unique<GameObject>(Transform(350, 260)) };
	controlsObject->AddComponent<ParagraphComponent>(
		"Move up/right -> DPAD UP\n"
		"Move up/left -> DPAD LEFT\n"
		"Move down/left -> DPAD DOWN\n"
		"Move down/right -> DPAD RIGHT\n"
		"Pause game -> START",
		Qbert::GetInstance().GetFontSmall()
	);

	auto moveOnPromptObject{ std::make_unique<GameObject>(Transform((640 / 2) - 180, 440)) };
	moveOnPromptObject->AddComponent<TextComponent>("Press ENTER or START to begin the 1st level", Qbert::GetInstance().GetFontSmall());

	m_pTutorialScene->Add(std::move(instructionsTitleObject));
	m_pTutorialScene->Add(std::move(descriptionObject));
	m_pTutorialScene->Add(std::move(wasdObject));
	m_pTutorialScene->Add(std::move(orObject));
	m_pTutorialScene->Add(std::move(controlsObject));
	m_pTutorialScene->Add(std::move(moveOnPromptObject));
}

void dae::SinglePlayerIntroGameState::OnEnter() {
	InputManager::GetInstance().ClearAllBindings();

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Enter, Keyboard::ActionType::Release },
		std::move(std::make_unique<ChangeGameStateCommand>(m_pSinglePlayerState))
	);

	InputManager::GetInstance().BindGamepadCommand(
		0,
		Gamepad::ButtonState{ Gamepad::Button::Start, Gamepad::ActionType::Release },
		std::move(std::make_unique<ChangeGameStateCommand>(m_pSinglePlayerState))
	);

	SceneManager::GetInstance().SetScene(m_pTutorialScene);
}
