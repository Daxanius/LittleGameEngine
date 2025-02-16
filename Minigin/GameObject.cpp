#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"

dae::GameObject::~GameObject() {
	m_Components.clear();
}

void dae::GameObject::FixedUpdate() {
	for (auto& kvs : m_Components) {
		kvs.second->FixedUpdate();
	}
}

void dae::GameObject::Update(float deltaTime){
	for (auto& kvs : m_Components) {
		kvs.second->Update(deltaTime);
	}

	RemoveQueuedComponents();

	// Run the post-update for all components
	for (auto& kvs : m_Components) {
		kvs.second->PostUpdate();
	}
}

void dae::GameObject::Render() const
{
	for (const auto& kvs : m_Components) {
		kvs.second->Render();
	}
}

void dae::GameObject::RemoveQueuedComponents() {
	for (const auto& id : m_ComponentsToBeRemoved) {
		m_Components.erase(id);
	}

	// After the components have been removed, the queue can be cleared
	m_ComponentsToBeRemoved.clear();
}