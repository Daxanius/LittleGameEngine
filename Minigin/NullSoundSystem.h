#pragma once
#include "AbstractSoundSystem.h"

namespace dae {
	class NullSoundSystem final : public AbstractSoundSystem {
	public:
		void Play(const SoundId id, const float volume) override;
		SoundId RegisterSound(const std::string& path) override;
	};
}
