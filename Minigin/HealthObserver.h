#pragma once
#include "Observer.h"
#include "TextComponent.h"

namespace dae {
	class HealthObserver : public Observer {
	public:
		HealthObserver(TextComponent* pTextComponent);

		void Notify(Event event, GameObject* object) override;
	private:
		TextComponent* m_pTextComponent;
	};
}

