#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

dae::GameObject::GameObject(Transform transform) : m_localTransform(std::move(transform)) {
}

dae::GameObject::~GameObject() {
	m_components.clear();
}

void dae::GameObject::SetParent(GameObject* pParent, bool keepWorldTransform) {
	// Check if it is even vladimir putin
	if (IsChild(pParent) || pParent == this || m_pParent == pParent) {
		return;
	}

	// Notify existing parent child got stolen lol
	if (m_pParent) {
		// Erase self from children lol
		std::erase_if(m_pParent->m_pChildren, [this](GameObject* child) {
			return child == this;
		});
	}
	
	// Set the current parent
	m_pParent = pParent;

	if (m_pParent) {
		m_pParent->m_pChildren.push_back(this);

		if (keepWorldTransform) {
			SetLocalTransform(GetWorldTransform() - pParent->GetWorldTransform());
		}
	} else {
		SetLocalTransform(GetWorldTransform());
	}

	MarkTransformDirty();
}

dae::GameObject* dae::GameObject::GetParent() {
	return m_pParent;
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

void dae::GameObject::Render() const {
	for (const auto& component : m_components) {
		component->Render();
	}
}

void dae::GameObject::SetLocalTransform(const Transform& transform) {
	m_localTransform = transform;
	MarkTransformDirty();
}

dae::Transform dae::GameObject::GetLocalTransform() const {
	return m_localTransform;
}

dae::Transform dae::GameObject::GetWorldTransform() {
	if (m_transformDirty) {
		UpdateWorldTransform();
	}

	return m_worldTransform;
}

bool dae::GameObject::IsChild(GameObject* pObj) const {
	for (const GameObject* child : m_pChildren) {
		if (child == pObj) {
			return true;
		}
	}

	return false;
}

std::vector<dae::GameObject*>& dae::GameObject::GetChildren() {
	return m_pChildren;
}

void dae::GameObject::MarkTransformDirty() {
	m_transformDirty = true;

	// Mark the transforms for all children dirty
	for (auto& child : m_pChildren) {
		child->MarkTransformDirty();
	}
}

void dae::GameObject::UpdateWorldTransform() {
	if (m_pParent) {
		m_worldTransform = m_localTransform + m_pParent->GetWorldTransform();
	} else {
		m_worldTransform = m_localTransform;
	}

	m_transformDirty = false;
}

void dae::GameObject::RemoveDestroyedComponents() {
	std::erase_if(m_components, [](const std::unique_ptr<BaseComponent>& component) {
		return component->IsDestroyed();
	});
}