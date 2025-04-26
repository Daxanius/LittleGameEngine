#include "SDLSoundSystem.h"

void dae::SDLSoundSystem::Play(const dae::SoundId, const float) {
}

dae::SoundId dae::SDLSoundSystem::RegisterSound(const std::string&) {
    return SoundId();
}
