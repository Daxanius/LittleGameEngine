#include "UggAndWrongwayComponent.h"
#include "LivesComponent.h"

dae::UggAndWrongwayComponent::UggAndWrongwayComponent(GameObject& pOwner, GridMovementComponent* pPlayerMovementComponent, LevelComponent* pLevelComponent, bool isUgg) 
 : BaseComponent(pOwner), m_pPlayerMovementComponent(pPlayerMovementComponent), m_pLevelComponent(pLevelComponent), m_isUgg(isUgg) {
	m_pOwnMovementComponent = GetComponent<GridMovementComponent>();
	m_pNavigationComponent = GetComponent<GridNavigationComponent>();
}

void dae::UggAndWrongwayComponent::Update(float) {
	if (m_pLevelComponent->LevelPaused()) return;

	int ownRow = m_pOwnMovementComponent->GetRow();
	int ownCol = m_pOwnMovementComponent->GetCol();
	int playerRow = m_pPlayerMovementComponent->GetRow();
	int playerCol = m_pPlayerMovementComponent->GetCol();

	if (!m_pOwnMovementComponent->IsJumping() &&
		!m_pPlayerMovementComponent->IsJumping() &&
		ownRow == playerRow && ownCol == playerCol) {
		m_pPlayerMovementComponent->GetComponent<LivesComponent>()->Kill();
		return;
	}

	if (m_pNavigationComponent && m_pNavigationComponent->HasArrived()) {
		int nextRow = ownRow - 1;
		int nextCol = m_isUgg ? ownCol + 1 : ownCol - 1;

		if (nextRow < 0 || nextCol < 0 || nextCol > nextRow) {
			GetOwner().Destroy(); // Fell off the grid
		} else {
			m_pNavigationComponent->SetTarget(nextRow, nextCol);
		}
	}
}
