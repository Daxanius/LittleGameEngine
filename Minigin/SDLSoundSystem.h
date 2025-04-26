#pragma once
#include "AbstractSoundSystem.h"
#include <memory>

namespace dae {
	class SDLSoundSystem final : public AbstractSoundSystem {
	public:
		void Play(const SoundId id, const float volume) override;
		SoundId RegisterSound(const std::string& path) override;

		// Delete these monkeys 
		SDLSoundSystem(const SDLSoundSystem& other) = delete;
		SDLSoundSystem(SDLSoundSystem&& other) noexcept = delete;
		SDLSoundSystem& operator=(const SDLSoundSystem& other) = delete;
		SDLSoundSystem& operator=(SDLSoundSystem&& other) noexcept = delete;
		virtual ~SDLSoundSystem() override = default;
	private:
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}
