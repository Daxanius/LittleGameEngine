#pragma once
#include "Observer.h"
#include "ServiceLocator.h"
#include "AbstractSoundSystem.h"
#include <string>

namespace dae {
	class SoundObserver : public Observer {
	public:
		SoundObserver();

		void Notify(Event event) override;
	private:
		SoundId m_changeSelectionSfx{};
		SoundId m_qbertJumpSfx{};

		float m_volume{ .2f };
	};
}