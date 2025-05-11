#include "LivesObserver.h"
#include "hash.h"

dae::LivesObserver::LivesObserver(RepeatingTextureComponent* pLivesTextureComponent) : m_pLivesTextureComponent(pLivesTextureComponent) {
}

void dae::LivesObserver::Notify(Event event) {
	switch (event.id) {
		case (make_sdbm_hash("killed")):
		{
			int lives = std::any_cast<int>(event.data);
			m_pLivesTextureComponent->SetRows(lives);
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
