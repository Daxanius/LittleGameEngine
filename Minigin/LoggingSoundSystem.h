#pragma once
#include "AbstractSoundSystem.h"
#include <memory>

namespace dae {
	class LoggingSoundSystem final : public AbstractSoundSystem {
	public:
		explicit LoggingSoundSystem(std::unique_ptr<AbstractSoundSystem> soundSystem);

		void Play(const SoundId id, const float volume) override;
		SoundId RegisterSound(const std::string& path) override;

		// Delete these monkeys 
		LoggingSoundSystem(const LoggingSoundSystem& other) = delete;
		LoggingSoundSystem(LoggingSoundSystem&& other) noexcept = delete;
		LoggingSoundSystem& operator=(const LoggingSoundSystem& other) = delete;
		LoggingSoundSystem& operator=(LoggingSoundSystem&& other) noexcept = delete;
		virtual ~LoggingSoundSystem() override = default;
	private:
		std::unique_ptr<AbstractSoundSystem> m_soundSystem;
	};
}