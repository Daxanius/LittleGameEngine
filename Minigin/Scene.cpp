#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::unique_ptr<GameObject>&& object) {
	m_objectsToAdd.emplace_back(std::move(object));
}

void Scene::RemoveAll() {
	m_objects.clear();
}

void dae::Scene::OnEnter() {
		ProcessPendingChanges();
}

void dae::Scene::FixedUpdate() {
	for (auto& object : m_objects) {
		if (object->IsEnabled()) {
			object->FixedUpdate();
		}
	}

	ProcessPendingChanges();
}

void Scene::Update(float deltaTime) {
	for(auto& object : m_objects) {
		if (object->IsEnabled()) {
			object->Update(deltaTime);
		}
	}

	ProcessPendingChanges();

	// PostUpdate should be called regardless
	// of when the object is enabled or disabled
	for(auto& object : m_objects) {
			object->PostUpdate();
	}
}

void Scene::Render() const {
	for (const auto& object : m_objects) {
		if (object->IsEnabled()) {
			object->Render();
		}
	}
}

void dae::Scene::ProcessPendingChanges() {
	for (auto& obj : m_objectsToAdd) {
		m_objects.push_back(std::move(obj));
	}
	m_objectsToAdd.clear();

	// Remove destroyed objects
	m_objects.erase(
		std::remove_if(m_objects.begin(), m_objects.end(),
			[](const std::unique_ptr<GameObject>& obj) {
				return obj->IsDestroyed();
			}), m_objects.end());
}