#pragma once
#include "Observer.h"
#include  "GameObject.h"

namespace dae {
	class AchievementObserver : public Observer {
		// Inherited via Observer
		void Notify(Event event, GameObject* object) override;
	};
}
