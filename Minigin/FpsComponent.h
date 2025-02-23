#pragma once
#include "GameObject.h"
#include "BaseComponent.h"
#include "TextComponent.h"

namespace dae {
	class FpsComponent final : public BaseComponent {
	public:
		FpsComponent(GameObject& pOwner);

		void FixedUpdate() override {};
		void Update(float deltaTime) override;
		void PostUpdate() override;
	  void Render() override {};

	private:
		TextComponent* m_pTextComponent{ nullptr };
	};
}
