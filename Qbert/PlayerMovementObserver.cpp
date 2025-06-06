#include "PlayerMovementObserver.h"
#include "GridMovementComponent.h"
#include "hash.h"

dae::PlayerMovementObserver::PlayerMovementObserver(SpriteComponent* pPlayerSpriteComponent, RhombilleGridComponent* pRhombilleGridComponent, LivesComponent* pLivesComponent, ScoreComponent* pScoreComponent, LevelComponent* pLevelComponent, RhombilleGridAnimationComponent* pRhombilleGridAnimationComponent)
	: m_pPlayerSpriteComponent(pPlayerSpriteComponent),
	m_pRhombilleGridComponent(pRhombilleGridComponent),
	m_pLivesComponent(pLivesComponent),
	m_pScoreComponent(pScoreComponent),
	m_pLevelComponent(pLevelComponent),
	m_pRhombileGridAnimationComponent(pRhombilleGridAnimationComponent)
{
}

void dae::PlayerMovementObserver::Notify(Event event) {
	switch (event.id) {
		case make_sdbm_hash("move_left"):
			m_pPlayerSpriteComponent->SetState(make_sdbm_hash("left"));
			break;
		case make_sdbm_hash("move_right"):
			m_pPlayerSpriteComponent->SetState(make_sdbm_hash("right"));
			break;
		case make_sdbm_hash("move_up"):
			m_pPlayerSpriteComponent->SetState(make_sdbm_hash("up"));
			break;
		case make_sdbm_hash("move_down"):
			m_pPlayerSpriteComponent->SetState(make_sdbm_hash("down"));
			break;
		case make_sdbm_hash("arrive"):
			GridMovementComponent::ArriveEventData data{ std::any_cast<GridMovementComponent::ArriveEventData>(event.data) };
			auto tile{ m_pRhombilleGridComponent->GetTile(data.row, data.col) };
			if (tile != nullptr) {
				if (tile->state == 0) {
					tile->state = 1;
					m_pScoreComponent->AddToScore(25);

					if (m_pRhombilleGridComponent->AreAllTilesState(1)) {
						m_pLevelComponent->NextRound();
						// m_pRhombilleGridComponent->SetVariant(m_pLevelComponent->GetRound());
						m_pRhombilleGridComponent->SetAllStates(0);
						m_pRhombileGridAnimationComponent->PlayAnimation();
					}
				}
			} else {
				m_pLivesComponent->Kill();
			}
			break;
	}
}
