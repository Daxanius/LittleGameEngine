#include "FpsComponent.h"

void dae::FpsComponent::Ready(GameObject* obj) {
	m_GameObject = obj;
	m_TextComponentPtr = obj->GetComponent<TextComponent>();
	assert(m_TextComponentPtr);
}

void dae::FpsComponent::Update(float deltaTime) {
	if (m_TextComponentPtr && deltaTime > 0.f) {
		const float fps = 1.0f / deltaTime;
		m_TextComponentPtr->SetText(std::to_string(static_cast<int>(std::roundf(fps))));
	}
}

void dae::FpsComponent::PostUpdate() {
	// Just set text to a nullptr for now, no rechecking for creating new components and stuff
	if (!m_GameObject->HasComponent<TextComponent>()) {
		m_TextComponentPtr = nullptr;
	}
}
