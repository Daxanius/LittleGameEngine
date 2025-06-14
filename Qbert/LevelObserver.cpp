#include "LevelObserver.h"
#include "hash.h"

dae::LevelObserver::LevelObserver(TextComponent* pRoundText) 
	: m_pRoundText(pRoundText) {
}

void dae::LevelObserver::Notify(const Event& event) {
	switch (event.id) {
		case make_sdbm_hash("next_round"):
		{
			int round{ event.GetValue<int>() };
			m_pRoundText->SetText("ROUND:" + std::to_string(round+1));
			break;
		}
	}
}
