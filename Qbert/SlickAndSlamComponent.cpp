#include "SlickAndSlamComponent.h"
#include "PlayerComponent.h"

dae::SlickAndSlamComponent::SlickAndSlamComponent(GameObject& pOwner, LevelComponent* pLevelComponent)
 : BaseComponent(pOwner), m_pLevelComponent(pLevelComponent) {
	m_pOwnMovementComponent = GetComponent<GridMovementComponent>();
	m_pNavigationComponent = GetComponent<GridNavigationComponent>();
}

void dae::SlickAndSlamComponent::Update(float) {
	if (m_pLevelComponent->LevelPaused()) {
		return;
	}

	int ownRow{ m_pOwnMovementComponent->GetRow() };
	int ownCol{ m_pOwnMovementComponent->GetCol() };

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
			GetOwner().Destroy();
		}
	}

	if (m_pOwnMovementComponent->HasArrived()) {
		auto tile{ m_pLevelComponent->GetRhombilleGrid()->GetTile(ownRow, ownCol) };
		if (tile != nullptr) {
			tile->state = std::max(tile->state -1, 0); // Revert the state of the tile
		}
	}

	if (m_pNavigationComponent != nullptr && m_pNavigationComponent->HasArrived()) {
		GetOwner().Destroy();
	}
}
