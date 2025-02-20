#include "Component.h"

dae::Component::Component(GameObject& pOwner) : m_pOwner(&pOwner) {
}

dae::GameObject& dae::Component::GetOwner() {
	return *m_pOwner;
}
