#pragma once
#include "GameObject.h"

namespace dae {
	class Component {
	public:
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Ready(GameObject*) {};

		virtual void FixedUpdate() {};
		virtual void Update(float) {};
		virtual void Render() const {};

	protected:
		Component() = default;
	};
}