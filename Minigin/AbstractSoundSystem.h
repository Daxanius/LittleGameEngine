#pragma once
#include <string>

namespace dae {
	using SoundId = unsigned short;

	class AbstractSoundSystem {
	public:
		virtual ~AbstractSoundSystem() = default;
		virtual void Play(const SoundId id, const float volume) = 0;
		virtual SoundId RegisterSound(const std::string& filePath) = 0;
		virtual void SetMuted(bool muted) = 0;
		virtual bool IsMuted() const = 0;

		AbstractSoundSystem() = default;
		AbstractSoundSystem(const AbstractSoundSystem& other) = delete;
		AbstractSoundSystem(AbstractSoundSystem&& other) noexcept = delete;
		AbstractSoundSystem& operator=(const AbstractSoundSystem& other) = delete;
		AbstractSoundSystem& operator=(AbstractSoundSystem&& other) noexcept = delete;
	};
}
