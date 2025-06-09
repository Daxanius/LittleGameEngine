#include "SlickAndSlamComponent.h"

dae::SlickAndSlamComponent::SlickAndSlamComponent(GameObject& pOwner, GridMovementComponent* pPlayerMovementComponent, LevelComponent* pLevelComponent)
 : BaseComponent(pOwner), m_pPlayerMovementComponent(pPlayerMovementComponent), m_pLevelComponent(pLevelComponent) {
	m_pOwnMovementComponent = GetComponent<GridMovementComponent>();
	m_pNavigationComponent = GetComponent<GridNavigationComponent>();
}

void dae::SlickAndSlamComponent::Update(float) {
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
		GetOwner().Destroy();
		return;
	}

	if (m_pOwnMovementComponent->HasArrived()) {
		auto tile{ m_pLevelComponent->GetRhombilleGrid().GetTile(ownRow, ownCol) };
		if (tile != nullptr) {
			tile->state = tile->state - 1 >= 0 ? tile->state - 1 : 0; // Revert the state of the tile
		}
	}

	if (m_pNavigationComponent != nullptr && m_pNavigationComponent->HasArrived()) {
		// TODO: observe how these guys move to make a correct implementation
		GetOwner().Destroy();
	}
}
