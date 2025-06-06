#include "PlayerComponent.h"

dae::PlayerComponent::PlayerComponent(GameObject& pOwner) : BaseComponent(pOwner) {
	m_pTextBalloonGo =	GetOwner().GetChildren().front();
	m_pLivesComponent = GetOwner().GetComponent<LivesComponent>();
}

void dae::PlayerComponent::Update(float) {
	
}