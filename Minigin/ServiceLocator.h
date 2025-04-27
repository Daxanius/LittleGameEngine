#pragma once
#include "Singleton.h"
#include "AbstractSoundSystem.h"
#include <memory>

namespace dae {
	class ServiceLocator final : public Singleton<ServiceLocator> {
	public:
		// Allows the service locator to initialze with default values (for example null sound system)
		ServiceLocator();

		AbstractSoundSystem& GetSoundSystem();
		void RegisterSoundSystem(std::unique_ptr<AbstractSoundSystem> soundSystem);

	private:
		std::unique_ptr<AbstractSoundSystem> m_soundSystemInstance;
	};
}
