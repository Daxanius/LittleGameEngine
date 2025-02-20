#include "FpsComponent.h"

dae::FpsComponent::FpsComponent(GameObject& pOwner) : BaseComponent(pOwner) {
	m_pTextComponent = GetOwner().GetComponent<TextComponent>();
	assert(m_pTextComponent);
}

void dae::FpsComponent::Update(float deltaTime) {
	if (deltaTime > 0.f) {
		const float fps = 1.0f / deltaTime;
		m_pTextComponent->SetText(std::to_string(static_cast<int>(std::roundf(fps))));
	}
}

void dae::FpsComponent::PostUpdate() {
	// Since this component cannot function anymore after the text has been destroyed, it will just destroy itself
	if (m_pTextComponent->IsDestroyed()) {
		Destroy();
	}
}
