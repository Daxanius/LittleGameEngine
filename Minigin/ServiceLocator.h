#pragma once
#include "Singleton.h"
#include <memory>

namespace dae {
	class AbstractSoundSystem;

	class ServiceLocator final : public Singleton<ServiceLocator> {
	public:
		// Allows the service locator to initialze with default values (for example null sound system)
		ServiceLocator();

		static AbstractSoundSystem& GetSoundSystem();
		static void RegisterSoundSystem(std::unique_ptr<AbstractSoundSystem> soundSystem);

	private:
		static std::unique_ptr<AbstractSoundSystem> m_soundSystemInstance;
	};
}
