#pragma once
#include <Observer.h>
#include "SpriteComponent.h"
#include "GridMovementComponent.h"

namespace dae {
	class UggAndWrongwayObserver final : public Observer {
	public:
		UggAndWrongwayObserver(SpriteComponent* pSpriteComponent);

		void Notify(Event event) override;

	private:
		SpriteComponent* m_pSpriteComponent{};
	};
}