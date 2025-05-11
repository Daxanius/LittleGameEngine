#include "Qbert.h"
#include "Scene.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "SelectionMenuComponent.h"
#include "LoadSceneCommand.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "RhombilleGridComponent.h"
#include "SpriteComponent.h"
#include "GridMovementComponent.h"
#include "PlayerMovementObserver.h"
#include "MoveCommand.h"
#include "hash.h"

dae::Qbert::Qbert() : m_pSoundObserver(std::make_shared<SoundObserver>()) {
	m_pFont = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 30);

	CreateLevelScene();
}

std::shared_ptr<dae::Font> dae::Qbert::GetFont() const {
	return m_pFont;
}

std::shared_ptr<dae::SoundObserver> dae::Qbert::GetSoundObserver() const {
	return m_pSoundObserver;
}

void dae::Qbert::SetState(std::shared_ptr<AbstractGameState> pGameState) {
	m_pGameState = pGameState;
	m_pGameState->OnEnter();
}

void dae::Qbert::CreateLevelScene() {




}
