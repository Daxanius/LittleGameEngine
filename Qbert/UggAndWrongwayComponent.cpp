#include "UggAndWrongwayComponent.h"
#include "LivesComponent.h"
#include "PlayerComponent.h"

dae::UggAndWrongwayComponent::UggAndWrongwayComponent(GameObject& pOwner, LevelComponent* pLevelComponent, bool isUgg) 
 : BaseComponent(pOwner), m_pLevelComponent(pLevelComponent), m_isUgg(isUgg) {
	m_pOwnMovementComponent = GetComponent<GridMovementComponent>();
	m_pNavigationComponent = GetComponent<GridNavigationComponent>();
}

void dae::UggAndWrongwayComponent::Update(float) {
	if (m_pLevelComponent->LevelPaused()) return;

	int ownRow = m_pOwnMovementComponent->GetRow();
	int ownCol = m_pOwnMovementComponent->GetCol();

	if (m_pOwnMovementComponent->IsJumping()) {
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
