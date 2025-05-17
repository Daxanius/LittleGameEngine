#include "LevelObserver.h"
#include "hash.h"

dae::LevelObserver::LevelObserver(TextComponent* pScoreText) : m_pScoreText(pScoreText) {
}

void dae::LevelObserver::Notify(Event event) {
	switch (event.id) {
		case make_sdbm_hash("score_increased"):
		{
			std::pair<int, int> score = std::any_cast<std::pair<int, int>>(event.data);
			m_pScoreText->SetText("SCORE: " + std::to_string(score.second));
			break;
		}
		case make_sdbm_hash("next_round"):
		case make_sdbm_hash("next_level"):
		{
			// TODO: call a thing to pause everything and play an animation
			break;
		}
	}
}
