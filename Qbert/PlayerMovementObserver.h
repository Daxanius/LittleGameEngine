#pragma once
#include "Observer.h"
#include "SpriteComponent.h"
#include "RhombilleGridComponent.h"
#include "RhombilleGridAnimationComponent.h"
#include "LivesComponent.h"
#include "LevelComponent.h"
#include "ScoreComponent.h"

namespace dae {
	class PlayerMovementObserver : public Observer {
	public:
		PlayerMovementObserver(SpriteComponent* pPlayerSpriteComponent, RhombilleGridComponent* pRhombilleGridComponent, LivesComponent* pLivesComponent, ScoreComponent* pScoreComponent, LevelComponent* pLevelComponent, RhombilleGridAnimationComponent* pRhombilleGridAnimationComponent);

		void Notify(Event event) override;
	private:
		SpriteComponent* m_pPlayerSpriteComponent;
		RhombilleGridComponent* m_pRhombilleGridComponent;
		RhombilleGridAnimationComponent* m_pRhombileGridAnimationComponent;
		LivesComponent* m_pLivesComponent;
		ScoreComponent* m_pScoreComponent;
		LevelComponent* m_pLevelComponent;
	};
}