#include "UggAndWrongwayObserver.h"
#include "hash.h"

dae::UggAndWrongwayObserver::UggAndWrongwayObserver(SpriteComponent* pSpriteComponent) 
	: m_pSpriteComponent(pSpriteComponent)
{

}

void dae::UggAndWrongwayObserver::Notify(const Event& event) {
	switch (event.id) {
		case (make_sdbm_hash("move_up_right")):
		case (make_sdbm_hash("move_up")):
			m_pSpriteComponent->SetState(make_sdbm_hash("roll1"));
			break;
		case (make_sdbm_hash("move_down_left")):
		case (make_sdbm_hash("move_down")):
			m_pSpriteComponent->SetState(make_sdbm_hash("roll2"));
			break;
		case (make_sdbm_hash("move_up_left")):
		case (make_sdbm_hash("move_left")):
			m_pSpriteComponent->SetState(make_sdbm_hash("roll3"));
			break;
		case (make_sdbm_hash("move_down_right")):
		case (make_sdbm_hash("move_right")):
			m_pSpriteComponent->SetState(make_sdbm_hash("roll4"));
			break;
		case (make_sdbm_hash("arrive")):
		{
			// m_pSpriteComponent->GetOwner().Destroy();
			break;
		}
	}
}