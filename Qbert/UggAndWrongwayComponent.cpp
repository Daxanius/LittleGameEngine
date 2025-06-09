#include "UggAndWrongwayComponent.h"
#include "LivesComponent.h"

dae::UggAndWrongwayComponent::UggAndWrongwayComponent(GameObject& pOwner, GridMovementComponent* pPlayerMovementComponent, LevelComponent* pLevelComponent) 
 : BaseComponent(pOwner), m_pPlayerMovementComponent(pPlayerMovementComponent), m_pLevelComponent(pLevelComponent) {
	m_pOwnMovementComponent = GetComponent<GridMovementComponent>();
	m_pNavigationComponent = GetComponent<GridNavigationComponent>();
}

void dae::UggAndWrongwayComponent::Update(float) {
	if (m_pLevelComponent->LevelPaused()) {
		return;
	}

	int ownRow{ m_pOwnMovementComponent->GetRow() };
	int ownCol{ m_pOwnMovementComponent->GetCol() };

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

	if (m_pNavigationComponent != nullptr && m_pNavigationComponent->HasArrived()) {
		GetOwner().Destroy();
	}
}
