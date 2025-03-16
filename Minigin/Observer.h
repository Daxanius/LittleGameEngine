#pragma once
#include "Event.h"

namespace dae {
	class GameObject;

	// https://share.daxanius.dev/s/yx96kZfiAsiJc2A
	class Observer {
	public:
		virtual ~Observer() = default;
		virtual void Notify(Event event, GameObject* object) = 0;

		Observer(const Observer& other) = delete;
		Observer(Observer&& other) = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) = delete;
	};
}