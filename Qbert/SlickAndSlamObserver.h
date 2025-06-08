#pragma once
#include <Observer.h>
#include "SpriteComponent.h"
#include "GridMovementComponent.h"

namespace dae {
	class SlickAndSlamObserver : public Observer {
	public:
		SlickAndSlamObserver(SpriteComponent* pSpriteComponent);

		void Notify(Event event) override;

	private:
		SpriteComponent* m_pSpriteComponent{};
	};
}

