#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::TextureComponent::TextureComponent(const std::string& filename) : Component() {
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureComponent::Ready(GameObject* obj) {
	m_Transform = obj->GetComponent<TransformComponent>();
	assert(m_Transform);
}

void dae::TextureComponent::Render() const {
	const auto& pos = m_Transform->GetPosition();
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}
