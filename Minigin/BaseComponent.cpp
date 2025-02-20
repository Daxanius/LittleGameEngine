#include "BaseComponent.h"

void dae::BaseComponent::Destroy() {
	m_destroyed = true;
}

bool dae::BaseComponent::IsDestroyed() const {
	return m_destroyed;
}

dae::BaseComponent::BaseComponent(GameObject& pOwner) : m_pOwner(&pOwner) {
}

dae::GameObject& dae::BaseComponent::GetOwner() {
	return *m_pOwner;
}
