#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::TextureComponent::TextureComponent(const std::string& filename) : Component() {
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureComponent::Ready(GameObject* obj) {
	m_GameObject = obj;
	m_TransformComponent = obj->GetComponent<TransformComponent>();
	assert(m_TransformComponent);
}

void dae::TextureComponent::Render() const {
	if (m_TransformComponent) {
		const auto& pos = m_TransformComponent->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void dae::TextureComponent::PostUpdate() {
	// Just set the transform to null for now
	if (!m_GameObject->HasComponent<TransformComponent>()) {
		m_TransformComponent = nullptr;
	}
}
