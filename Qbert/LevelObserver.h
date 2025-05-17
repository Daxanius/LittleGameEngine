#pragma once
#include <Observer.h>
#include "TextComponent.h"

namespace dae {
	class LevelObserver : public Observer {
	public:
		LevelObserver(TextComponent* pScoreText);

		void Notify(Event event) override;

	private:
		TextComponent* m_pScoreText{ nullptr };
	};
}
