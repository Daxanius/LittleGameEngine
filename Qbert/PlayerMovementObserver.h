#pragma once
#include "Observer.h"
#include "SpriteComponent.h"
#include "RhombilleGridComponent.h"
#include "LivesComponent.h"
#include "LevelComponent.h"
#include "ScoreComponent.h"

namespace dae {
	class PlayerMovementObserver : public Observer {
	public:
		PlayerMovementObserver(SpriteComponent* pPlayerSpriteComponent, RhombilleGridComponent* pRhombilleGridComponent, LivesComponent* pLivesComponent, ScoreComponent* pScoreComponent, LevelComponent* pLevelComponent);

		void Notify(Event event) override;
	private:
		SpriteComponent* m_pPlayerSpriteComponent;
		RhombilleGridComponent* m_pRhombilleGridComponent;
		LivesComponent* m_pLivesComponent;
		ScoreComponent* m_pScoreComponent;
		LevelComponent* m_pLevelComponent;
	};
}