#include "SceneManager.h"
#include <algorithm>
#include <iostream>

void dae::SceneManager::AddScene(std::unique_ptr<Scene>&& scene) {
	m_scenesToAdd.emplace_back(std::move(scene));
}

void dae::SceneManager::RemoveScene(const std::string& name) {
	m_scenesToRemove.emplace_back(name);
}

void dae::SceneManager::SetScene(const std::string& name) {
	m_nextScene = name;

	// If there's no active scene yet, set it immediately
	if (m_activeScene == nullptr) {
		ProcessUpdates();
	}
}

dae::Scene* dae::SceneManager::GetActiveScene() const {
	return m_activeScene;
}

void dae::SceneManager::FixedUpdate() {
	if (m_activeScene != nullptr) {
		m_activeScene->FixedUpdate();
	}
}

void dae::SceneManager::Update(float deltaTime)
{
	if (m_activeScene != nullptr) {
		m_activeScene->Update(deltaTime);
	}

	ProcessUpdates();
}

void dae::SceneManager::Render()
{
	if (m_activeScene != nullptr) {
		m_activeScene->Render();
	}
}

void dae::SceneManager::ProcessUpdates() {
	for (const auto& name : m_scenesToRemove) {
		m_scenes.erase(name);
	}
	m_scenesToRemove.clear();

	std::vector<Scene*> newlyAdded;
	for (auto& scene : m_scenesToAdd) {
		Scene* rawPtr{ scene.get() };
		m_scenes[scene->GetName()] = std::move(scene);
		newlyAdded.push_back(rawPtr);
	}

	m_scenesToAdd.clear();
	for (auto* scene : newlyAdded) {
		scene->Setup(); // This allows setup to dynamically add new scenes
	}

	if (m_nextScene.has_value()) {
		auto it = m_scenes.find(m_nextScene.value());
		if (it != m_scenes.end()) {
			m_activeScene = it->second.get();
			m_nextScene.reset();
			m_activeScene->Enter();
		} else {
			std::cerr << "Scene \"" << m_nextScene.value() << "\" not found.\n";
			m_nextScene.reset();
		}
	}
}
