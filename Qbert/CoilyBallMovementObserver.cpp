#include "CoilyBallMovementObserver.h"
#include "hash.h"
#include "CoilyStateSnake.h"
#include "RhombilleGridComponent.h"
#include "SpriteComponent.h"

dae::CoilyBallMovementObserver::CoilyBallMovementObserver(CoilyComponent* pCoilyComponent)
	: m_pCoilyComponent(pCoilyComponent) {
	m_pSpriteComponent = m_pCoilyComponent->GetOwner().GetComponent<SpriteComponent>();
	assert(m_pSpriteComponent != nullptr);
}

void dae::CoilyBallMovementObserver::Notify(const Event& event) {
	switch (event.id) {
		case (make_sdbm_hash("move_up")):
		case (make_sdbm_hash("move_down")):
		case (make_sdbm_hash("move_left")):
		case (make_sdbm_hash("move_right")):
		case (make_sdbm_hash("move_up_right")):
		case (make_sdbm_hash("move_up_left")):
		case (make_sdbm_hash("move_down_right")):
		case (make_sdbm_hash("move_down_left")):
			m_pSpriteComponent->SetState(make_sdbm_hash("ball_jump"));
			break;

		case (make_sdbm_hash("arrive")):
			m_pSpriteComponent->SetState(make_sdbm_hash("ball_idle"));
			break;
	}
}
