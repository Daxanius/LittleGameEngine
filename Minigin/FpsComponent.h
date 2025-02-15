#pragma once
#include "GameObject.h"
#include "Component.h"
#include "TextComponent.h"

namespace dae {
	class FpsComponent : public Component {
	public:
		void Ready(GameObject* obj) override;
		void Update(float deltaTime) override;
		
	private:
		TextComponent* m_Text{ nullptr };
	};
}
