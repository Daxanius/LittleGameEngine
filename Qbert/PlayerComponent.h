#pragma once
#include <BaseComponent.h>
#include "GameObject.h"
#include "GridMovementComponent.h"
#include "SpriteComponent.h"
#include "LivesComponent.h"
#include <memory>

namespace dae {
	class PlayerComponent final : public BaseComponent {
	public:
		PlayerComponent(GameObject& pOwner);

		void ShowTextBalloon();
		void HideTextBalloon();

		GridMovementComponent* GetMovementComponent();
		LivesComponent* GetLivesComponent();

		void Reset();

		void Kill();
		
		bool HasDied() const;

		void FixedUpdate() override {};
		void Update(float) override {};
		void PostUpdate() override {};
		void Render() override {};
	private:
		GridMovementComponent* m_pGridMovementComponent{};
		SpriteComponent* m_pSpriteComponent{};
		LivesComponent* m_pLivesComponent{};
		GameObject* m_pTextBalloonGo{};

		bool m_died{};
	};
}
