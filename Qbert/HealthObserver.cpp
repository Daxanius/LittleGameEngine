#include "HealthObserver.h"
#include "hash.h"

dae::HealthObserver::HealthObserver(TextComponent* pTextComponent) : Observer(), m_pTextComponent(pTextComponent) {
}

void dae::HealthObserver::Notify(Event event, GameObject*) {
	switch (event.id) {
		case make_sdbm_hash("health_decreased"):
		case make_sdbm_hash("health_increased"):
		{
			std::pair<int, int> scoreInfo{ any_cast<std::pair<int, int>>(event.data) };
			m_pTextComponent->SetText("Lives: " + std::to_string(scoreInfo.second));
			break;
		}
	}
}
