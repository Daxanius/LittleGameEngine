#include "PlayerMovementObserver.h"
#include "hash.h"

dae::PlayerMovementObserver::PlayerMovementObserver(SpriteComponent* pPlayerSpriteComponent) : m_pPlayerSpriteComponent(pPlayerSpriteComponent) {
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
	}
}
