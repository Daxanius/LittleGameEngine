#include "SlickAndSlamObserver.h"
#include "hash.h"

dae::SlickAndSlamObserver::SlickAndSlamObserver(SpriteComponent* pSpriteComponent) 
	: m_pSpriteComponent(pSpriteComponent)
{
}

void dae::SlickAndSlamObserver::Notify(Event event) {
	switch (event.id) {
		case (make_sdbm_hash("move_up_right")):
		case (make_sdbm_hash("move_up")):
			m_pSpriteComponent->SetState(make_sdbm_hash("right"));
			break;
		case (make_sdbm_hash("move_down_left")):
		case (make_sdbm_hash("move_down")):
			m_pSpriteComponent->SetState(make_sdbm_hash("left"));
			break;
		case (make_sdbm_hash("move_up_left")):
		case (make_sdbm_hash("move_left")):
			m_pSpriteComponent->SetState(make_sdbm_hash("left"));
			break;
		case (make_sdbm_hash("move_down_right")):
		case (make_sdbm_hash("move_right")):
			m_pSpriteComponent->SetState(make_sdbm_hash("right"));
			break;
		case (make_sdbm_hash("arrive")):
		{
			// m_pSpriteComponent->GetOwner().Destroy();
			break;
		}
	}
}
