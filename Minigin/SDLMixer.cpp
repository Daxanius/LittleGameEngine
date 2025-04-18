#pragma once

#include "AudioPlayer.h"

#include <string>
#include <SDL_mixer.h>
#include <iostream>

class dae::AudioPlayer::Impl {
public:
	Impl() {
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
			std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << '\n';
		}
	}

	~Impl() {
		if (currentMusic_) {
			Mix_FreeMusic(currentMusic_);
		}

		if (currentChunk_) {
			Mix_FreeChunk(currentChunk_);
		}

		Mix_CloseAudio();
	}

	void PlaySound(const std::string& filepath) {
		if (currentMusic_) {
			Mix_HaltMusic();
			Mix_FreeMusic(currentMusic_);
			currentMusic_ = nullptr;
		}

		currentMusic_ = Mix_LoadMUS(filepath.c_str());
		if (!currentMusic_) {
			std::cerr << "Failed to load music: " << Mix_GetError() << '\n';
			return;
		}

		if (Mix_PlayMusic(currentMusic_, 1) == -1) {
			std::cerr << "Failed to play music: " << Mix_GetError() << '\n';
		}
	}

	void PlayChunk(const std::string& filepath) {
		if (currentChunk_) {
			Mix_HaltChannel(-1);
			Mix_FreeChunk(currentChunk_);
			currentChunk_ = nullptr;
		}

		currentChunk_ = Mix_LoadWAV(filepath.c_str());
		if (!currentChunk_) {
			std::cerr << "Failed to load chunk: " << Mix_GetError() << '\n';
			return;
		}

		if (Mix_PlayChannel(-1, currentChunk_, 0) == -1) {
			std::cerr << "Failed to play chunk: " << Mix_GetError() << '\n';
		}
	}
private:
	Mix_Music* currentMusic_ = nullptr;
	Mix_Chunk* currentChunk_ = nullptr;
};
