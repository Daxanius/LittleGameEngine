#include "PlayerLivesObserver.h"
#include "hash.h"

dae::PlayerLivesObserver::PlayerLivesObserver(RepeatingTextureComponent* pLivesTextureComponent, GameObject* pTextBalloonGameObject) : m_pLivesTextureComponent(pLivesTextureComponent), m_pTextBalloonGameObject(pTextBalloonGameObject) {
}

void dae::PlayerLivesObserver::Notify(Event event) {
	switch (event.id) {
		case (make_sdbm_hash("killed")):
		{
			int lives = std::any_cast<int>(event.data);
			m_pLivesTextureComponent->SetRows(lives);
			m_pTextBalloonGameObject->Enable();
			break;
		}

		case (make_sdbm_hash("lives_added")):
		{
			std::pair<int, int> values = std::any_cast<std::pair<int, int>>(event.data);
			m_pLivesTextureComponent->SetRows(values.second);
			break;
		}
	}
}
