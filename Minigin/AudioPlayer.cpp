#include "AudioPlayer.h"
#include "SDLMixer.cpp"

dae::AudioPlayer::AudioPlayer()
	: m_pImpl(std::make_unique<Impl>()) {
}

dae::AudioPlayer::~AudioPlayer() = default;

void dae::AudioPlayer::PlaySound(const std::string& filepath) {
	m_pImpl->PlaySound(filepath);
}

void dae::AudioPlayer::PlayChunk(const std::string& filepath) {
	m_pImpl->PlayChunk(filepath);
}
