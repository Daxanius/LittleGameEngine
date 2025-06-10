#pragma once
#include "Observer.h"
#include "RepeatingTextureComponent.h"
#include "LevelComponent.h"
#include "PlayerComponent.h"
#include "GameObject.h"
#include "Command.h"
#include "Scene.h"

namespace dae {
	class PlayerLivesObserver : public Observer {
	public:
		PlayerLivesObserver(
			RepeatingTextureComponent* pLivesTextureComponent, 
			PlayerComponent* pPlayerComponent, 
			LevelComponent* pLevelComponent
		);
		
		void Notify(const Event& event) override;

	private:
		RepeatingTextureComponent* m_pLivesTextureComponent;
		LevelComponent* m_pLevelComponent;
		PlayerComponent* m_pPlayerComponent;
	};
}
