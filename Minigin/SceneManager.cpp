#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>

void dae::SceneManager::AddScene(std::shared_ptr<Scene> scene) {
	m_scenes.emplace_back(scene);
}

void dae::SceneManager::RemoveScene(std::shared_ptr<Scene> scene) {
	std::erase(m_scenes, scene);
}

void dae::SceneManager::SetScene(std::shared_ptr<Scene> scene) {
	m_scenes.clear();
	m_scenes.emplace_back(scene);
}

void dae::SceneManager::FixedUpdate() {
	for (auto& scene : m_scenes) {
		scene->FixedUpdate();
	}
}

void dae::SceneManager::Update(float deltaTIme)
{
	for(auto& scene : m_scenes) {
		scene->Update(deltaTIme);
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_scenes) {
		scene->Render();
	}
}