#include "ScoreObserver.h"
#include "hash.h"

dae::ScoreObserver::ScoreObserver(TextComponent* pScoreText)
	: m_pScoreText(pScoreText) {
}

void dae::ScoreObserver::Notify(const Event& event) {
	switch (event.id) {
		case make_sdbm_hash("score_increased"):
		{
			auto score{ event.GetValue<std::pair<int, int>>() };
			m_pScoreText->SetText("SCORE:" + std::to_string(score.second));
			break;
		}
	}
}
