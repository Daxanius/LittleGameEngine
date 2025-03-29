#pragma once
#include "Observer.h"
#include  "GameObject.h"

namespace dae {
	class AchievementObserver : public Observer {
	public:
		AchievementObserver() = default;

		// Inherited via Observer
		void Notify(Event event, GameObject* object) override;
	};
}
