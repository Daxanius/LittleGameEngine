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

		virtual void Ready([[maybe_unused]] GameObject* obj) {};

		virtual void FixedUpdate() {};
		virtual void Update([[maybe_unused]] float deltaTime) {};
		virtual void PostUpdate() {}; // Used to remove objects if they have been deleted
		virtual void Render() const {};

	protected:
		Component() = default;
	};
}