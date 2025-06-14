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

		
		FpsComponent(const FpsComponent&) = delete;
		FpsComponent& operator=(const FpsComponent&) = delete;
		FpsComponent(FpsComponent&&) = delete;
		FpsComponent& operator=(FpsComponent&&) = delete;
		~FpsComponent() = default;
	private:
		TextComponent* m_pTextComponent{ nullptr };
	};
}
