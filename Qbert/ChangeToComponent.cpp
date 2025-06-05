#include "ChangeToComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::ChangeToComponent::ChangeToComponent(GameObject& pOwner, LevelComponent* pLevelComponent, const std::string& texturePath, int tileWidth, int tileHeight, float scale) 
	: BaseComponent(pOwner), m_pLevelComponent(pLevelComponent), m_tileWidth(tileWidth), m_tileHeight(tileHeight), m_scale(scale) {
		m_pTexture = ResourceManager::GetInstance().LoadTexture(texturePath);

}

void dae::ChangeToComponent::Update(float) {
}

void dae::ChangeToComponent::Render() {
	const auto& worldPosition{ GetOwner().GetWorldTransform().GetPosition() };
	int variant{ m_pLevelComponent->GetRound() };

	
	Renderer::GetInstance().RenderTexture(
		*m_pTexture, 
		worldPosition.x,
		worldPosition.y,
		static_cast<float>(m_tileWidth) * m_scale, 
		static_cast<float>(m_tileHeight) * m_scale, 
		m_tileWidth * variant, 0, 
		m_tileWidth,
		m_tileHeight
	);
}
