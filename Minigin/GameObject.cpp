#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

dae::GameObject::~GameObject() {
	m_components.clear();
}

void dae::GameObject::FixedUpdate() {
	for (auto& component : m_components) {
		component->FixedUpdate();
	}
}

void dae::GameObject::Update(float deltaTime){
	for (auto& component : m_components) {
		if (!component->IsDestroyed()) {
			component->Update(deltaTime);
		}
	}

	RemoveDestroyedComponents();

	// Run the post-update for all components
	for (auto& component : m_components) {
		component->PostUpdate();
	}
}

void dae::GameObject::Render() const
{
	for (const auto& component : m_components) {
		component->Render();
	}
}

void dae::GameObject::RemoveDestroyedComponents() {
	std::erase_if(m_components, [](const std::unique_ptr<BaseComponent>& component) {
		return component->IsDestroyed();
	});
}