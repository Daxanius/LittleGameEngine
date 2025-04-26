#pragma once
#include "SoundSystem.h"
#include <memory>

namespace dae {
	class LoggingSoundSystem final : public SoundSystem {
	public:
		explicit LoggingSoundSystem(std::unique_ptr<SoundSystem> soundSystem);

		void Play(const SoundId id, const float volume) override;
		SoundId RegisterSound(const std::string& path) override;

		// Delete these monkeys 
		LoggingSoundSystem(const LoggingSoundSystem& other) = delete;
		LoggingSoundSystem(LoggingSoundSystem&& other) noexcept = delete;
		LoggingSoundSystem& operator=(const LoggingSoundSystem& other) = delete;
		LoggingSoundSystem& operator=(LoggingSoundSystem&& other) noexcept = delete;
		virtual ~LoggingSoundSystem() override = default;
	private:
		std::unique_ptr<SoundSystem> m_soundSystem;
	};
}