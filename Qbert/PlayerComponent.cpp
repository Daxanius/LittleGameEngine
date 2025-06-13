#include "PlayerComponent.h"
#include "hash.h"

dae::PlayerComponent::PlayerComponent(GameObject& pOwner) : BaseComponent(pOwner) {
	m_pGridMovementComponent = GetComponent<GridMovementComponent>();
	m_pLivesComponent = GetComponent<LivesComponent>();
	m_pSpriteComponent = GetComponent<SpriteComponent>();
	m_pScoreComponent = GetComponent<ScoreComponent>();
	m_pTextBalloonGo =	GetOwner().GetChildren().front(); // First child is the text balloon
}

void dae::PlayerComponent::ShowTextBalloon() {
	m_pTextBalloonGo->Enable();
}

void dae::PlayerComponent::HideTextBalloon() {
	m_pTextBalloonGo->Disable();
}

dae::SpriteComponent* dae::PlayerComponent::GetSpriteComponent() {
	return m_pSpriteComponent;
}

dae::GridMovementComponent* dae::PlayerComponent::GetMovementComponent() {
	return m_pGridMovementComponent;
}

void dae::PlayerComponent::AddGameOverCommand(std::unique_ptr<Command> pCommand) {
	m_gameOverCommands.emplace_back(std::move(pCommand));
}

dae::LivesComponent* dae::PlayerComponent::GetLivesComponent() {
	return m_pLivesComponent;
}

dae::ScoreComponent* dae::PlayerComponent::GetScoreComponent() {
	return m_pScoreComponent;
}

void dae::PlayerComponent::Reset() {
	HideTextBalloon();
	DisableFreeMovement();
	SetInvulnerable(false);

	if (m_died) {
		if (m_shouldGoBack) {
			m_pGridMovementComponent->GoToPrevPosition();
		}
		m_died = false;
	} else {
		m_pGridMovementComponent->ResetPosition();
		m_pSpriteComponent->SetState(make_sdbm_hash("right"));
	}
}

void dae::PlayerComponent::Kill(bool shouldGoBack) {
	if (m_pLivesComponent->IsInvulnerable()) {
		m_died = false;
		return;
	}

	ShowTextBalloon();
	m_died = true;
	m_shouldGoBack = shouldGoBack;
	m_pLivesComponent->Kill();

	if (m_pLivesComponent->GetLives() <= 0) {
		for (auto& command : m_gameOverCommands) {
			command->Execute();
		}
	}
}

bool dae::PlayerComponent::HasDied() const {
	return m_died;
}

bool dae::PlayerComponent::IsInvulnerable() const {
	return m_pLivesComponent->IsInvulnerable();
}

void dae::PlayerComponent::SetInvulnerable(bool value) {
	m_pLivesComponent->SetInvulnerable(value);
}

void dae::PlayerComponent::EnableFreeMovement() {
	m_pGridMovementComponent->Disable();
	m_pGridMovementComponent->CancelJump();
}

void dae::PlayerComponent::DisableFreeMovement() {
	m_pGridMovementComponent->Enable();
}
