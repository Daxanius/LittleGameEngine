#include "PlayerMovementObserver.h"
#include "GridMovementComponent.h"
#include "hash.h"

dae::PlayerMovementObserver::PlayerMovementObserver(PlayerComponent* pPlayerComponent, LevelComponent* pLevelComponent)
	: m_pPlayerComponent(pPlayerComponent),
	m_pLevelComponent(pLevelComponent)
{
}

void dae::PlayerMovementObserver::Notify(const Event& event) {
	switch (event.id) {
		case make_sdbm_hash("move_left"):
			m_pPlayerComponent->GetSpriteComponent()->SetState(make_sdbm_hash("left"));
			break;
		case make_sdbm_hash("move_right"):
			m_pPlayerComponent->GetSpriteComponent()->SetState(make_sdbm_hash("right"));
			break;
		case make_sdbm_hash("move_up"):
			m_pPlayerComponent->GetSpriteComponent()->SetState(make_sdbm_hash("up"));
			break;
		case make_sdbm_hash("move_down"):
			m_pPlayerComponent->GetSpriteComponent()->SetState(make_sdbm_hash("down"));
			break;
		case make_sdbm_hash("arrive"):
		{
			auto rhombilleGrid{ m_pLevelComponent->GetRhombilleGrid() };
			GridMovementComponent::ArriveEventData data{ std::any_cast<GridMovementComponent::ArriveEventData>(event.data) };
			auto tile{ rhombilleGrid->GetTile(data.row, data.col) };
			if (tile != nullptr) {
				if (m_pLevelComponent->FlickTile(tile)) {
					m_pPlayerComponent->GetScoreComponent()->AddToScore(25);
				}

				if (rhombilleGrid->AreAllTilesState(m_pLevelComponent->GetRequiredTileState())) {
					// m_pRhombilleGridComponent->SetVariant(m_pLevelComponent->GetRound());
					if (m_pLevelComponent->NextRound()) {
						rhombilleGrid->SetAllStates(0);
						m_pLevelComponent->GetRhombileGridAnimationComponent()->PlayAnimation();
					}
				}
			} else {
				if (!m_pLevelComponent->CheckSpinningDiscs()) {
					m_pPlayerComponent->Kill(true);
				}
			}
			break;
		}
	}
}
