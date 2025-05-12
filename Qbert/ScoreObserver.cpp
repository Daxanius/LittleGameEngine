#include "ScoreObserver.h"
#include "hash.h"

dae::ScoreObserver::ScoreObserver(TextComponent* pScoreText) : m_pScoreText(pScoreText) {
}

void dae::ScoreObserver::Notify(Event event) {
	switch (event.id) {
		case make_sdbm_hash("score_increased"):
		{
			std::pair<int, int> score = std::any_cast<std::pair<int, int>>(event.data);
			m_pScoreText->SetText("SCORE: " + std::to_string(score.second));
			break;
		}
	}
}
