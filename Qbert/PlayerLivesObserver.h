#pragma once
#include "Observer.h"
#include "RepeatingTextureComponent.h"
#include "LevelComponent.h"
#include "GameObject.h"

namespace dae {
	class PlayerLivesObserver : public Observer {
	public:
		PlayerLivesObserver(RepeatingTextureComponent* pLivesTextureComponent, GameObject* pTextBalloonGameObject, LevelComponent* pLevelComponent);
		
		void Notify(Event event) override;

	private:
		RepeatingTextureComponent* m_pLivesTextureComponent;
		LevelComponent* m_pLevelComponent;
		GameObject* m_pTextBalloonGameObject;
	};
}
