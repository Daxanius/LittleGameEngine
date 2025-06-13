#include "LoggingSoundSystem.h"
#include <iostream>

dae::LoggingSoundSystem::LoggingSoundSystem(std::unique_ptr<AbstractSoundSystem> soundSystem) : m_soundSystem(std::move(soundSystem)) {
}

void dae::LoggingSoundSystem::Play(const SoundId id, const float volume) {
	if (m_muted) {
		return;
	}

	std::cout << "Playing sound with id " << id << " at volume " << volume << std::endl;
	m_soundSystem->Play(id, volume);
}

dae::SoundId dae::LoggingSoundSystem::RegisterSound(const std::string& path) {
	SoundId id{ m_soundSystem->RegisterSound(path) };
	std::cout << "Registered sound at path " << path << " with id " << id << std::endl;
	return id;
}

void dae::LoggingSoundSystem::SetMuted(bool muted) {
	m_muted = muted;
}

bool dae::LoggingSoundSystem::IsMuted() const {
	return m_muted;
}
