#pragma once
#include "GameObject.h"
#include "Component.h"
#include "TextComponent.h"

namespace dae {
	class FpsComponent : public Component {
	public:
		void Ready(GameObject* obj) override;
		void Update(float deltaTime) override;
		void PostUpdate() override;

	private:
		GameObject* m_GameObject{ nullptr };

		TextComponent* m_TextComponentPtr{ nullptr };
	};
}
