#include "PauseScene.h"
#include "TextureComponent.h"

dae::PauseScene::PauseScene() 
	: Scene("Pause") {
}

void dae::PauseScene::OnSetup() {
	auto backgroundImageObject{ std::make_unique<GameObject>() };
	backgroundImageObject->AddComponent<TextureComponent>("Pause Screen.png");
	Add(std::move(backgroundImageObject));
}