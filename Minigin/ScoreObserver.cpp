#include "ScoreObserver.h"
#include "hash.h"

dae::ScoreObserver::ScoreObserver(TextComponent* pTextComponent) : Observer(), m_pTextComponent(pTextComponent) {
}

void dae::ScoreObserver::Notify(Event event, GameObject*) {
	switch (event.id) {
		case make_sdbm_hash("score_decreased"):
		case make_sdbm_hash("score_increased"):
		{
			std::pair<int, int> scoreInfo{ any_cast<std::pair<int, int>>(event.data) };
			m_pTextComponent->SetText("Score: " + std::to_string(scoreInfo.second));
			break;
		}
	}
}
