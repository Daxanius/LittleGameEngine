#pragma once
#include <BaseComponent.h>

namespace dae {
	class LevelComponent : public BaseComponent {
	public:
		LevelComponent(GameObject& pOwner);

		void FixedUpdate() override {};
		void Update(float deltaTime) override;
		void PostUpdate() override {};
		void Render() override {};
	private:
		int round{};
		int level{};
	};
}
