#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>
#include <deque>
#include <string>
#include <variant>

namespace dae {
	class AudioPlayer;

	struct PlayMusicCommand {
		std::string filepath;
	};

	struct PlayChunkCommand {
		std::string filepath;
	};

	using AudioCommand = std::variant<PlayMusicCommand, PlayChunkCommand>;

	class AudioManager {
	public:
		AudioManager();
		~AudioManager();

		// Queue a request (can be called from any thread)
		void QueueCommand(const AudioCommand& command);

	private:
		void ProcessQueue();

		std::deque<AudioCommand> m_CommandQueue;
		std::mutex m_Mutex;

		std::condition_variable m_CondVar;
		std::atomic<bool> m_Running;
		std::thread m_WorkerThread;

		std::unique_ptr<AudioPlayer> m_Player;
	};
}
