#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::TextureComponent::TextureComponent(GameObject& pOwner, const std::string& filename, float scale) 
	: BaseComponent(pOwner), m_scale(scale) {
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureComponent::Render() {
	const auto& pos = GetOwner().GetWorldTransform().GetPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y, m_pTexture->GetSize().x * m_scale, m_pTexture->GetSize().y * m_scale);
}
