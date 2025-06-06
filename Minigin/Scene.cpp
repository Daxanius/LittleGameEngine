#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object) {
	m_objectsToAdd.push_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object) {
	m_objectsToRemove.push_back(std::move(object));
}

void Scene::RemoveAll() {
	m_objectsToRemove.insert(
		m_objectsToRemove.end(),
		m_objects.begin(),
		m_objects.end()
	);
}

void dae::Scene::FixedUpdate() {
	ProcessPendingChanges();

	for (auto& object : m_objects) {
		if (object->IsEnabled()) {
			object->FixedUpdate();
		}
	}
}

void Scene::Update(float deltaTime) {
	ProcessPendingChanges();

	for(auto& object : m_objects) {
		if (object->IsEnabled()) {
			object->Update(deltaTime);
		}
	}

	RemoveDestroyedObjects();
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

	for (auto& objToRemove : m_objectsToRemove) {
		m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), objToRemove), m_objects.end());
	}
	m_objectsToRemove.clear();
}

void dae::Scene::RemoveDestroyedObjects() {
	for (const auto& object : m_objects) {
		if (object->IsDestroyed()) {
			Remove(object); // Add the object to the removal queue to be removed from the scene
		}
	}
}
