#pragma once
#include "Observer.h"
#include "RepeatingTextureComponent.h"

namespace dae {
	class LivesObserver : public Observer {
	public:
		LivesObserver(RepeatingTextureComponent* pLivesTextureComponent);
		
		void Notify(Event event) override;

	private:
		RepeatingTextureComponent* m_pLivesTextureComponent;
	};
}
