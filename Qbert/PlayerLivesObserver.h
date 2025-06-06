#pragma once
#include "Observer.h"
#include "RepeatingTextureComponent.h"
#include "GameObject.h"

namespace dae {
	class PlayerLivesObserver : public Observer {
	public:
		PlayerLivesObserver(RepeatingTextureComponent* pLivesTextureComponent, GameObject* pTextBalloonGameObject);
		
		void Notify(Event event) override;

	private:
		RepeatingTextureComponent* m_pLivesTextureComponent;
		GameObject* m_pTextBalloonGameObject;
	};
}
