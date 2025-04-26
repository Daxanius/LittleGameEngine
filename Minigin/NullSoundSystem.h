#pragma once
#include "SoundSystem.h"

namespace dae {
	class NullSoundSystem final : public SoundSystem {
	public:
		void Play(const SoundId id, const float volume) override;
		SoundId RegisterSound(const std::string& path) override;
	};
}
