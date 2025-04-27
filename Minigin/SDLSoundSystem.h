#pragma once
#include "AbstractSoundSystem.h"
#include <memory>

namespace dae {
	class SDLSoundSystem final : public AbstractSoundSystem {
	public:
		SDLSoundSystem();
		void Play(const SoundId id, const float volume) override;
		SoundId RegisterSound(const std::string& filePath) override;

		// Delete these monkeys 
		SDLSoundSystem(const SDLSoundSystem& other) = delete;
		SDLSoundSystem(SDLSoundSystem&& other) noexcept = delete;
		SDLSoundSystem& operator=(const SDLSoundSystem& other) = delete;
		SDLSoundSystem& operator=(SDLSoundSystem&& other) noexcept = delete;
		virtual ~SDLSoundSystem() override;
	private:
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}
