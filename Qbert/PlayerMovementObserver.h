#pragma once
#include "Observer.h"
#include "SpriteComponent.h"
#include "RhombilleGridComponent.h"
#include "LivesComponent.h"

namespace dae {
	class PlayerMovementObserver : public Observer {
	public:
		PlayerMovementObserver(SpriteComponent* pPlayerSpriteComponent, RhombilleGridComponent* pRhombilleGridComponent, LivesComponent* pLivesComponent);

		void Notify(Event event) override;
	private:
		SpriteComponent* m_pPlayerSpriteComponent;
		RhombilleGridComponent* m_pRhombilleGridComponent;
		LivesComponent* m_pLivesComponent;
	};
}