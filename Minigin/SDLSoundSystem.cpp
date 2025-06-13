#include "SDLSoundSystem.h"
#include <queue>
#include <mutex>
#include <iostream>
#include "SDL_mixer.h"

class dae::SDLSoundSystem::Impl {
public:
	// A small sound class that keeps track of its audio data
	class Sound {
	public:
		Sound(const std::string& filePath) : m_filePath(filePath) {

		}

		~Sound() {
			if (m_pChunk != nullptr) {
				Mix_FreeChunk(m_pChunk);
				m_pChunk = nullptr;
			}
		}

		void Load() {
			// No need to load it if it's already loaded
			if (m_pChunk) {
				return;
			}

			m_pChunk = Mix_LoadWAV(m_filePath.c_str());
		}

		void Play(float volume) {
			if (m_pChunk) {
				Mix_VolumeChunk(m_pChunk, static_cast<int>(volume * MIX_MAX_VOLUME));
				Mix_PlayChannel(-1, m_pChunk, 0);
			}
		}

		const std::string& FilePath() {
			return m_filePath;
		}

		Sound(const Sound& other) = delete;
		Sound(Sound&& other) noexcept = delete;
		Sound& operator=(const Sound& other) = delete;
		Sound& operator=(Sound&& other) noexcept = delete;
	private:
		std::string m_filePath;
		Mix_Chunk* m_pChunk{ nullptr };
	};

	struct PlayInfo {
		dae::SoundId id;
		float volume;
	};

	Impl() : m_initialized(false), m_running(true) {
		std::lock_guard<std::mutex> lock(m_mutex); // Just to be sure

		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == 0) {
			m_initialized = true;
		} else {
			std::cerr << "Could not initialize audio subsystem" << std::endl;
		}

		m_thread = std::thread(&dae::SDLSoundSystem::Impl::ProcessSounds, this);
	}

	~Impl() {
		// Set running to false
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_running = false;
		}

		m_conditionVariable.notify_one();

		m_thread.join(); // Join the processing thread before closing down audio
		Mix_CloseAudio();
	}

	void Play(const dae::SoundId id, const float volume) {
		if (!m_initialized || m_muted) {
			return;
		}

		// Lock the mutex and add the sound play request to the queue
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_audioQueue.push(PlayInfo{ id, volume });
		}

		m_conditionVariable.notify_one();
	}

	void SetMuted(bool muted) {
		m_muted = muted;
	}

	bool IsMuted() const {
		return m_muted;
	}

	dae::SoundId RegisterSound(const std::string& filePath) {
		std::lock_guard<std::mutex> lock(m_mutex);

		// Look through all sounds and compare paths
		// Since this is not intended to run in a hot code path
		// doing this is fine, a hashmap would be overkill since we would
		// only fetch sounds by key for registering sounds, not for playing sounds,
		// which is a way more common occurence.
		for (size_t i = 0; i < m_sounds.size(); ++i) {
			if (m_sounds[i]->FilePath() == filePath) {
				return static_cast<dae::SoundId>(i); // Already registered, just return the ID
			}
		}

		// Not found, register new sound
		m_sounds.emplace_back(std::make_unique<Sound>(filePath));
		return static_cast<dae::SoundId>(m_sounds.size() - 1);
	}

private:
	void ProcessSounds() {
		// I read member variables in this scope because then the mutex would stay locked :/
		while (true) {
			PlayInfo info{};
			{
				std::unique_lock<std::mutex> lock(m_mutex);
				m_conditionVariable.wait(lock, [this] { return !m_audioQueue.empty() || !m_running; });

				if (!m_running || m_audioQueue.empty() || !m_initialized) {
					break;
				}

				info = m_audioQueue.front();
				m_audioQueue.pop();
			}

			Sound* sound = m_sounds[info.id].get();
			sound->Load();						// Make sure the sound is loaded (loading does its own checks)
			sound->Play(info.volume); // Play the sound with the provided volume
		}
	}

	std::queue<PlayInfo> m_audioQueue;

	std::vector<std::unique_ptr<Sound>> m_sounds;

	// Threading stuffs
	std::condition_variable m_conditionVariable;
	std::mutex m_mutex;
	std::thread m_thread;

	bool m_initialized;
	bool m_running; // Determines whether we should keep processing the queue
	bool m_muted{};
};

dae::SDLSoundSystem::~SDLSoundSystem() = default;

void dae::SDLSoundSystem::SetMuted(bool muted) {
	m_pImpl->SetMuted(muted);
}

bool dae::SDLSoundSystem::IsMuted() const {
	return m_pImpl->IsMuted();
}

dae::SDLSoundSystem::SDLSoundSystem() : m_pImpl(std::make_unique<dae::SDLSoundSystem::Impl>()) {
	
}

void dae::SDLSoundSystem::Play(const dae::SoundId id, const float volume) {
	m_pImpl->Play(id, volume);
}

dae::SoundId dae::SDLSoundSystem::RegisterSound(const std::string& filePath) {
	return m_pImpl->RegisterSound(filePath);
}
