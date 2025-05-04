#pragma once
#include "Observer.h"
#include "SpriteComponent.h"

namespace dae {
	class PlayerMovementObserver : public Observer {
	public:
		PlayerMovementObserver(SpriteComponent* pPlayerSpriteComponent);

		void Notify(Event event) override;
	private:
		SpriteComponent* m_pPlayerSpriteComponent;
	};
}