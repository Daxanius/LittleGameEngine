#pragma once
#include "Singleton.h"
#include <memory>

namespace dae {
	class SoundSystem;

	class ServiceLocator final : public Singleton<ServiceLocator> {
	public:
		// Allows the service locator to initialze with default values (for example null sound system)
		ServiceLocator();

		static SoundSystem& GetSoundSystem();
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem> soundSystem);

	private:
		static std::unique_ptr<SoundSystem> m_soundSystemInstance;
	};
}
