#pragma once
#include "Observer.h"
#include "SpriteComponent.h"
#include "RhombilleGridComponent.h"
#include "RhombilleGridAnimationComponent.h"
#include "LivesComponent.h"
#include "LevelComponent.h"
#include "ScoreComponent.h"
#include "PlayerComponent.h"

namespace dae {
	class PlayerMovementObserver : public Observer {
	public:
		PlayerMovementObserver(PlayerComponent* pPlayerComponent, LevelComponent* pLevelComponent);

		void Notify(const Event& event) override;
	private:
		PlayerComponent* m_pPlayerComponent;
		LevelComponent* m_pLevelComponent;
	};
}