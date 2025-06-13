#include "CoilyStateSnake.h"
#include "CoilyComponent.h"
#include "PlayerComponent.h"
#include "hash.h"

dae::CoilyStateSnake::CoilyStateSnake(CoilyComponent* pCoilyComponent) : AbstractCoilyState(pCoilyComponent) {
	m_pGridMovementComponent = GetCoilyComponent()->GetOwner().GetComponent<GridMovementComponent>();
	assert(m_pGridMovementComponent != nullptr);

	m_pSpriteComponent = GetCoilyComponent()->GetOwner().GetComponent<SpriteComponent>();
	assert(m_pSpriteComponent != nullptr);

	m_pGridNavigationComponent = GetCoilyComponent()->GetOwner().GetComponent<GridNavigationComponent>();
	assert(m_pGridNavigationComponent != nullptr);

	m_pCoilySnakeMovementObserver = std::make_shared<CoilySnakeMovementObserver>(pCoilyComponent);
}

void dae::CoilyStateSnake::OnEnter() {
	m_pSpriteComponent->SetState(make_sdbm_hash("idle_up"));
	m_pGridMovementComponent->GetSubject().AddObserver(m_pCoilySnakeMovementObserver);
	m_pGridNavigationComponent->Enable();
}

void dae::CoilyStateSnake::Update(float) {
	if (m_pGridMovementComponent->IsJumping()) {
		return;
	}

	const auto& players = GetCoilyComponent()->GetLevel()->GetPlayers();

	int ownRow = m_pGridMovementComponent->GetRow();
	int ownCol = m_pGridMovementComponent->GetCol();

	float minDistance = std::numeric_limits<float>::max();
	int targetRow = ownRow;
	int targetCol = ownCol;

	for (auto player : players) {
		const auto playerMovementComponent = player->GetMovementComponent();

		int playerRow = playerMovementComponent->GetRow();
		int playerCol = playerMovementComponent->GetCol();

		// If the player is jumping, target their destination
		if (playerMovementComponent->IsJumping()) {
			playerRow = playerMovementComponent->GetTargetRow();
			playerCol = playerMovementComponent->GetTargetCol();
		}

		// Compute squared distance to target nearest player
		int dRow = ownRow - playerRow;
		int dCol = ownCol - playerCol;
		float distanceSquared = static_cast<float>(dRow * dRow + dCol * dCol);

		if (distanceSquared < minDistance) {
			minDistance = distanceSquared;
			targetRow = playerRow;
			targetCol = playerCol;
		}
	}

	// Target the closest player
	m_pGridNavigationComponent->SetTarget(targetRow, targetCol);
}

void dae::CoilyStateSnake::OnExit() {
	m_pGridNavigationComponent->Disable();
	m_pGridMovementComponent->GetSubject().RemoveObserver(m_pCoilySnakeMovementObserver);
}
