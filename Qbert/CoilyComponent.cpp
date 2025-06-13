#include "CoilyComponent.h"
#include "LivesComponent.h"

dae::CoilyComponent::CoilyComponent(GameObject& pOwner, GridMovementComponent* pPlayerMovementComponent, LevelComponent* pLevelComponent) 
	: BaseComponent(pOwner), m_pPlayerMovementComponent(pPlayerMovementComponent), m_pLevelComponent(pLevelComponent) {
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

void dae::CoilyComponent::Update(float deltaTime) {
	if (m_pLevelComponent->LevelPaused()) {
		return;
	}

	m_pCurrentState->Update(deltaTime);
	
	int ownRow{ m_pOwnMovementComponent->GetRow() };
	int ownCol{ m_pOwnMovementComponent->GetCol() };

	if (m_pLevelComponent->GetRhombilleGrid().GetTile(ownRow, ownCol) == nullptr) {
		GetOwner().Destroy();
		return;
	}

	int playerRow{ m_pPlayerMovementComponent->GetRow() };
	int playerCol{ m_pPlayerMovementComponent->GetCol() };

	if (!m_pOwnMovementComponent->IsJumping() && 
			!m_pPlayerMovementComponent->IsJumping() && 
			ownRow == playerRow && 
			ownCol == playerCol
			) {
		m_pPlayerMovementComponent->GetComponent<LivesComponent>()->Kill();
		return;
	}
}