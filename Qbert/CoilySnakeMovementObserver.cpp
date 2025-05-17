#include "CoilySnakeMovementObserver.h"
#include "hash.h"

dae::CoilySnakeMovementObserver::CoilySnakeMovementObserver(CoilyComponent* pCoilyComponent, GridMovementComponent* pTargetMovementComponent) 
: m_pCoilyComponent(pCoilyComponent), m_pTargetMovementComponent(pTargetMovementComponent) {
	m_pSpriteComponent = m_pCoilyComponent->GetOwner().GetComponent<SpriteComponent>();
	assert(m_pSpriteComponent != nullptr);
}

void dae::CoilySnakeMovementObserver::Notify(Event event) {
	switch (event.id) {
		case (make_sdbm_hash("move_up_right")):
		case (make_sdbm_hash("move_up")):
			m_pSpriteComponent->SetState(make_sdbm_hash("jump_up"));
			m_lastDirection = Direction::Up;
			break;
		case (make_sdbm_hash("move_down_left")):
		case (make_sdbm_hash("move_down")):
			m_pSpriteComponent->SetState(make_sdbm_hash("jump_down"));
			m_lastDirection = Direction::Down;
			break;
		case (make_sdbm_hash("move_up_left")):
		case (make_sdbm_hash("move_left")):
			m_pSpriteComponent->SetState(make_sdbm_hash("jump_left"));
			m_lastDirection = Direction::Left;
			break;
		case (make_sdbm_hash("move_down_right")):
		case (make_sdbm_hash("move_right")):
			m_pSpriteComponent->SetState(make_sdbm_hash("jump_right"));
			m_lastDirection = Direction::Right;
			break;
		case (make_sdbm_hash("arrive")):
		{
			switch (m_lastDirection) {
				case Direction::Up:
					m_pSpriteComponent->SetState(make_sdbm_hash("idle_up"));
					break;
				case Direction::Down:
					m_pSpriteComponent->SetState(make_sdbm_hash("idle_down"));
					break;
				case Direction::Left:
					m_pSpriteComponent->SetState(make_sdbm_hash("idle_left"));
					break;
				case Direction::Right:
					m_pSpriteComponent->SetState(make_sdbm_hash("idle_right"));
					break;
			}

			break;
		}
	}
}
