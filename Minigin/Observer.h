#pragma once
#include "Event.h"

namespace dae {
	class GameObject;

	// https://share.daxanius.dev/s/yx96kZfiAsiJc2A
	class Observer {
	public:
		virtual ~Observer() = default;
		virtual void Notify(const Event& event) = 0;
	};
}