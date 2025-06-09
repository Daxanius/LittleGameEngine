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
	m_pFontLarge = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 30);
	m_pFontMedium = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 22);
	m_pFontSmall = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 16);
}

std::shared_ptr<dae::Font> dae::Qbert::GetFontLarge() const {
	return m_pFontLarge;
}

std::shared_ptr<dae::Font> dae::Qbert::GetFontMedium() const {
	return m_pFontMedium;
}

std::shared_ptr<dae::Font> dae::Qbert::GetFontSmall() const {
	return m_pFontSmall;
}

std::shared_ptr<dae::SoundObserver> dae::Qbert::GetSoundObserver() const {
	return m_pSoundObserver;
}

void dae::Qbert::SetState(std::shared_ptr<AbstractGameState> pGameState) {
	m_pGameState = pGameState;
	m_pGameState->OnEnter();
}
