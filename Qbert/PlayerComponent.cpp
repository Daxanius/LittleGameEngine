#include "PlayerComponent.h"
#include "hash.h"

dae::PlayerComponent::PlayerComponent(GameObject& pOwner) : BaseComponent(pOwner) {
	m_pGridMovementComponent = GetComponent<GridMovementComponent>();
	m_pLivesComponent = GetComponent<LivesComponent>();
	m_pSpriteComponent = GetComponent<SpriteComponent>();
	m_pTextBalloonGo =	GetOwner().GetChildren().front(); // First child is the text balloon
}

void dae::PlayerComponent::ShowTextBalloon() {
	m_pTextBalloonGo->Enable();
}

void dae::PlayerComponent::HideTextBalloon() {
	m_pTextBalloonGo->Disable();
}

dae::GridMovementComponent* dae::PlayerComponent::GetMovementComponent() {
	return m_pGridMovementComponent;
}

dae::LivesComponent* dae::PlayerComponent::GetLivesComponent() {
	return m_pLivesComponent;
}

void dae::PlayerComponent::Reset() {
	HideTextBalloon();

	if (m_died) {
		m_pGridMovementComponent->GoToPrevPosition();
	} else {
		m_pGridMovementComponent->ResetPosition();
		m_pSpriteComponent->SetState(make_sdbm_hash("right"));
	}
}

void dae::PlayerComponent::Kill() {
	ShowTextBalloon();
	m_died = true;
}

bool dae::PlayerComponent::HasDied() const {
	return m_died;
}