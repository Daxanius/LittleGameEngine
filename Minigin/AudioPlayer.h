#pragma once

#include <memory>
#include <string>

namespace dae {
	class AudioPlayer {
	public:
		AudioPlayer();
		~AudioPlayer();

		void PlaySound(const std::string& filepath);
		void PlayChunk(const std::string& filepath);

	private:
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}
