#pragma once
#include <Observer.h>
#include "TextComponent.h"

namespace dae {
	class LevelObserver : public Observer {
	public:
		LevelObserver(TextComponent* pScoreText, TextComponent* pRoundText, TextComponent* pLevelText);

		void Notify(const Event& event) override;

	private:
		TextComponent* m_pScoreText{ nullptr };
		TextComponent* m_pRoundText{ nullptr };
		TextComponent* m_pLevelText{ nullptr };
	};
}
