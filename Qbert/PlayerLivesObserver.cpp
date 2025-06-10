#include "PlayerLivesObserver.h"
#include "hash.h"

dae::PlayerLivesObserver::PlayerLivesObserver(RepeatingTextureComponent* pLivesTextureComponent, PlayerComponent* pPlayerComponent, LevelComponent* pLevelComponent) 
	: m_pLivesTextureComponent(pLivesTextureComponent), m_pPlayerComponent(pPlayerComponent), m_pLevelComponent(pLevelComponent) {
}

void dae::PlayerLivesObserver::Notify(const Event& event) {
	switch (event.id) {
		case (make_sdbm_hash("killed")):
		{
			int lives = std::any_cast<int>(event.data);
			m_pLivesTextureComponent->SetRows(lives);
			m_pPlayerComponent->Kill();
			m_pLevelComponent->ResetLevel();

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
