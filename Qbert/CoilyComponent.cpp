#include "CoilyComponent.h"
#include "PlayerComponent.h"

dae::CoilyComponent::CoilyComponent(GameObject& pOwner, LevelComponent* pLevelComponent) 
	: BaseComponent(pOwner), m_pLevelComponent(pLevelComponent) {
	m_pOwnMovementComponent = GetComponent<GridMovementComponent>();
}

void dae::CoilyComponent::SetState(std::shared_ptr<AbstractCoilyState> pState) {
	if (m_pCurrentState) {
		m_pCurrentState->OnExit();
	}

	m_pCurrentState = std::move(pState);
	if (m_pCurrentState) {
		m_pCurrentState->OnEnter();
	}
}

dae::LevelComponent* dae::CoilyComponent::GetLevel() const {
	return m_pLevelComponent;
}

void dae::CoilyComponent::Update(float deltaTime) {
	if (m_pLevelComponent->LevelPaused()) {
		return;
	}

	if (m_pOwnMovementComponent->IsJumping()) {
		return;
	}

	m_pCurrentState->Update(deltaTime);
	
	int ownRow{ m_pOwnMovementComponent->GetRow() };
	int ownCol{ m_pOwnMovementComponent->GetCol() };

	if (m_pLevelComponent->GetRhombilleGrid()->GetTile(ownRow, ownCol) == nullptr) {
		m_subject.Notify("coily_fall");
		GetOwner().Destroy();
		return;
	}

	for (auto player : m_pLevelComponent->GetPlayers()) {
		if (player->GetMovementComponent()->IsJumping()) {
			continue;
		}

		int playerRow{ player->GetMovementComponent()->GetRow() };
		int playerCol{ player->GetMovementComponent()->GetCol() };

		if (ownRow == playerRow && ownCol == playerCol) {
			player->Kill();
		}
	}
}

dae::Subject& dae::CoilyComponent::GetSubject() {
	return m_subject;
}