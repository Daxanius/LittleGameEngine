#pragma once
#include "GameObject.h"
#include "Component.h"
#include "TextComponent.h"

namespace dae {
	class FpsComponent final : public Component {
	public:
		FpsComponent(GameObject& pOwner);

		void FixedUpdate() override {};
		void Update(float deltaTime) override;
		void PostUpdate() override;
	  void Render() const override {};

	private:
		TextComponent* m_pTextComponent{ nullptr };
	};
}
