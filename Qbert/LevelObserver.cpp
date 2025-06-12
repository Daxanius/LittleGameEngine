#include "LevelObserver.h"
#include "hash.h"

dae::LevelObserver::LevelObserver(TextComponent* pScoreText, TextComponent* pRoundText, TextComponent* pLevelText) 
	: m_pScoreText(pScoreText), m_pRoundText(pRoundText), m_pLevelText(pLevelText) {
}

void dae::LevelObserver::Notify(const Event& event) {
	switch (event.id) {
		case make_sdbm_hash("score_increased"):
		{
			auto score{ event.GetValue<std::pair<int, int>>() };
			m_pScoreText->SetText("SCORE:" + std::to_string(score.second));
			break;
		}
		case make_sdbm_hash("next_round"):
		{
			int round{ event.GetValue<int>() };
			m_pRoundText->SetText("ROUND:" + std::to_string(round+1));
			break;
		}
	}
}
