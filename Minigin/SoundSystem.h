#pragma once
#include <string>

namespace dae {
	using SoundId = unsigned short;

	class SoundSystem {
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(const SoundId id, const float volume) = 0;
		virtual SoundId RegisterSound(const std::string& path) = 0;
	};
}
