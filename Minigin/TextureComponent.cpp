#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::TextureComponent::TextureComponent(GameObject& pOwner, const std::string& filename) : BaseComponent(pOwner) {
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
	m_pTransformComponent = GetOwner().GetComponent<TransformComponent>();
	assert(m_pTransformComponent);
}

void dae::TextureComponent::Render() const {
	const auto& pos = m_pTransformComponent->GetPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}

void dae::TextureComponent::PostUpdate() {
	// I can't live without youu!
	if (!GetOwner().HasComponent<TransformComponent>()) {
		Destroy();
	}
}
