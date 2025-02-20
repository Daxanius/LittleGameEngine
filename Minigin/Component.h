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

		virtual void FixedUpdate() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void PostUpdate()  = 0; // Used to remove objects if they have been deleted
		virtual void Render() const = 0;

	protected:
		explicit Component(GameObject& pOwner);

		GameObject& GetOwner();

	private:
		GameObject* m_pOwner;
	};
}