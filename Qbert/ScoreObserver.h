#pragma once
#include <Observer.h>
#include "TextComponent.h"

namespace dae {
	class ScoreObserver : public Observer {
	public:
		ScoreObserver(TextComponent* pScoreText);

		void Notify(Event event) override;

	private:
		TextComponent* m_pScoreText{ nullptr };
	};
}
