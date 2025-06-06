#pragma once
#include <BaseComponent.h>
#include "GameObject.h"
#include "LivesComponent.h"
#include "memory"

namespace dae {
	class PlayerComponent final : public BaseComponent {
	public:
		PlayerComponent(GameObject& pOwner);

		void FixedUpdate() override {};
		void Update(float deltaTime) override;
		void PostUpdate() override {};
		void Render() override {};
	private:
		LivesComponent* m_pLivesComponent{};
		GameObject* m_pTextBalloonGo{};
	};
}
