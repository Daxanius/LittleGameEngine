#pragma once
#include "Observer.h"
#include "TextComponent.h"

namespace dae {
	class ScoreObserver : public Observer {
	public:
		ScoreObserver(TextComponent* pTextComponent);

		// Inherited via Observer
		void Notify(Event event, GameObject* object) override;

	private:
		TextComponent* m_pTextComponent;
	};
}