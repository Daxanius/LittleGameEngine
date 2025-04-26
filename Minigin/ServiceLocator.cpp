#include "ServiceLocator.h"
#include "NullSoundSystem.h"

// Initialize with default services
dae::ServiceLocator::ServiceLocator() {
	m_soundSystemInstance = std::make_unique<NullSoundSystem>();
}

dae::SoundSystem& dae::ServiceLocator::GetSoundSystem() {
	return *m_soundSystemInstance;
}

void dae::ServiceLocator::RegisterSoundSystem(std::unique_ptr<SoundSystem> soundSystem) {
	m_soundSystemInstance = soundSystem == nullptr ? std::make_unique<NullSoundSystem>() : std::move(soundSystem);
}
