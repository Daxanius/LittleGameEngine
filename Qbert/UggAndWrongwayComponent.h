#pragma once
#include <BaseComponent.h>
#include "PlayerComponent.h"

namespace dae {
	class UggAndWrongwayComponent final : public BaseComponent {
	public:
		void FixedUpdate() override {};
		void Update(float) override {};
		void PostUpdate() override {};
		void Render() override {};

	private:
	};
}
