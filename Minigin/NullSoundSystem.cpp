#include "NullSoundSystem.h"

void dae::NullSoundSystem::Play(const SoundId, const float) {
	return;
}

dae::SoundId dae::NullSoundSystem::RegisterSound(const std::string&) {
	return SoundId();
}
