#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>

void dae::SceneManager::AddScene(std::shared_ptr<Scene> scene) {
	m_pendingAdditions.emplace_back(scene);
}

void dae::SceneManager::RemoveScene(std::shared_ptr<Scene> scene) {
	m_pendingRemovals.emplace_back(scene);
}

void dae::SceneManager::SetScene(std::shared_ptr<Scene> scene) {
	m_pendingSceneReplacement = scene;
}

std::shared_ptr<dae::Scene> dae::SceneManager::GetActiveScene() const {
	return m_scenes.empty() ? nullptr : m_scenes.front();
}

void dae::SceneManager::FixedUpdate() {
	for (auto& scene : m_scenes) {
		scene->FixedUpdate();
	}
}

void dae::SceneManager::Update(float deltaTIme)
{
	ApplyPendingChanges();
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

void dae::SceneManager::ApplyPendingChanges() {
	if (m_pendingSceneReplacement) {
		m_scenes.clear();
		m_scenes.emplace_back(m_pendingSceneReplacement);
		m_pendingSceneReplacement.reset();
		m_pendingAdditions.clear();
		m_pendingRemovals.clear();
		return;
	}

	// Remove pending scenes
	for (const auto& scene : m_pendingRemovals) {
		std::erase(m_scenes, scene);
	}

	m_pendingRemovals.clear();

	// Add new scenes
	for (const auto& scene : m_pendingAdditions) {
		m_scenes.emplace_back(scene);
	}
	m_pendingAdditions.clear();
}
