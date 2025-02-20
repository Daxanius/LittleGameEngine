#include "FpsComponent.h"

dae::FpsComponent::FpsComponent(GameObject& pOwner) : BaseComponent(pOwner) {
	m_pTextComponent = GetOwner().GetComponent<TextComponent>();
	assert(m_pTextComponent);
}

void dae::FpsComponent::Update(float deltaTime) {
	if (m_pTextComponent && deltaTime > 0.f) {
		const float fps = 1.0f / deltaTime;
		m_pTextComponent->SetText(std::to_string(static_cast<int>(std::roundf(fps))));
	}
}

void dae::FpsComponent::PostUpdate() {
	// Just set text to a nullptr for now, no rechecking for creating new components and stuff
	if (!GetOwner().HasComponent<TextComponent>()) {
		m_pTextComponent = nullptr;
	}
}
