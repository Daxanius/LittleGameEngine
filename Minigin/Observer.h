#pragma once
#include "Event.h"
#include "GameObject.h"

namespace dae {
	// https://share.daxanius.dev/s/yx96kZfiAsiJc2A
	class Observer {
	public:
		virtual ~Observer() = default;
		virtual void Notify(Event event, GameObject* object) = 0;
	};
}