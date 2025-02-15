#include "FpsComponent.h"

void dae::FpsComponent::Ready(GameObject* obj) {
	m_Text = obj->GetComponent<TextComponent>();
	assert(m_Text);
}

void dae::FpsComponent::Update(float deltaTime) {
	const float fps = 1.0f / deltaTime;
	m_Text->SetText(std::to_string(static_cast<int>(std::roundf(fps))));
}
