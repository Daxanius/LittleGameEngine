#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

dae::GameObject::~GameObject() {
	m_Components.clear();
}

void dae::GameObject::FixedUpdate() {
	for (auto& component : m_Components) {
		component->FixedUpdate();
	}
}

void dae::GameObject::Update(float deltaTime){
	for (auto& component : m_Components) {
		component->Update(deltaTime);
	}

	// Run the post-update for all components
	for (auto& component : m_Components) {
		component->PostUpdate();
	}

	RemoveDestroyedComponents();
}

void dae::GameObject::Render() const
{
	for (const auto& component : m_Components) {
		component->Render();
	}
}

void dae::GameObject::RemoveDestroyedComponents() {
	std::erase_if(m_Components, [](const std::unique_ptr<BaseComponent>& component) {
		return component->IsDestroyed();
	});
}