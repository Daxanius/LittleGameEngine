#include "BaseComponent.h"

dae::BaseComponent::BaseComponent(GameObject& pOwner) : m_pOwner(&pOwner) {
}

void dae::BaseComponent::Destroy() {
	m_destroyed = true;
}

bool dae::BaseComponent::IsDestroyed() const {
	return m_destroyed;
}

dae::GameObject& dae::BaseComponent::GetOwner() {
	return *m_pOwner;
}

void dae::BaseComponent::Enable() {
	m_enabled = true;
}

void dae::BaseComponent::Disable() {
	m_enabled = false;
}

bool dae::BaseComponent::IsEnabled() const {
	return m_enabled;
}