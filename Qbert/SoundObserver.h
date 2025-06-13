#pragma once
#include "Observer.h"
#include "ServiceLocator.h"
#include "AbstractSoundSystem.h"
#include <string>

namespace dae {
	class SoundObserver : public Observer {
	public:
		SoundObserver();

		void Notify(const Event& event) override;
	private:
		void Play(SoundId sound) const;

		SoundId m_changeSelectionSfx{};
		SoundId m_qbertJumpSfx{};
		SoundId m_discLandSfx{};
		SoundId m_discLiftSfx{};
		SoundId m_swearingSfx{};
		SoundId m_roundCompleteSfx{};
		SoundId m_slickSamCaughtSfx{};
		SoundId m_coilyFallSfx{};
		SoundId m_coilySnakeJumpSfx{};
		SoundId m_coilyEggJumpSfx{};
		SoundId m_enemyJumpSfx{};

		float m_volume{ .2f };
		AbstractSoundSystem& m_soundSystem;
	};
}