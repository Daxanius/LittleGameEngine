#include "BaseComponent.h"

dae::BaseComponent::BaseComponent(GameObject& pOwner) : m_pOwner(&pOwner) {
}

dae::GameObject& dae::BaseComponent::GetOwner() {
	return *m_pOwner;
}
