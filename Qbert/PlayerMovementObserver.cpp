#include "PlayerMovementObserver.h"
#include "GridMovementComponent.h"
#include "hash.h"

dae::PlayerMovementObserver::PlayerMovementObserver(SpriteComponent* pPlayerSpriteComponent, RhombilleGridComponent* pRhombilleGridComponent, LivesComponent* pLivesComponent) 
	: m_pPlayerSpriteComponent(pPlayerSpriteComponent), m_pRhombilleGridComponent(pRhombilleGridComponent), m_pLivesComponent(pLivesComponent) {
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
				tile->state = 1;
			} else {
				m_pLivesComponent->Kill();
			}
			break;
	}
}
