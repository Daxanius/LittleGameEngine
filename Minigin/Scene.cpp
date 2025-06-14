#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"

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

void dae::Scene::Setup() {
	m_objects.clear();
	m_objectsToAdd.clear();
	OnSetup();
}

void dae::Scene::Enter() {
	ProcessPendingChanges();
	OnEnter();
}

const std::string& dae::Scene::GetName() const {
	return m_name;
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

	// PostUpdate should be called regardless
	// of when the object is enabled or disabled
	for(auto& object : m_objects) {
			object->PostUpdate();
			m_sortDirty = m_sortDirty || object->IsZDirty() || object->IsDestroyed();
	}

	ProcessPendingChanges();
}

void dae::Scene::Render() const {
	if (m_sortDirty) {
		// Rebuild and sort the list
		m_sortedRenderables.clear();
		m_sortedRenderables.reserve(m_objects.size());

		for (const auto& obj : m_objects) {
				m_sortedRenderables.emplace_back(obj.get());
				obj->ClearZDirty(); // Clear Z-dirty flag
		}

		std::sort(m_sortedRenderables.begin(), m_sortedRenderables.end(),
			[](const GameObject* a, const GameObject* b) {
				return a->GetWorldTransform().GetZ() < b->GetWorldTransform().GetZ();
			});

		m_sortDirty = false;
	}

	// Render using cached sorted list
	for (const GameObject* obj : m_sortedRenderables) {
		if (obj->IsEnabled()) {
			obj->Render();
		}
	}
}

void dae::Scene::SetName(const std::string& name) {
	m_name = name;
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