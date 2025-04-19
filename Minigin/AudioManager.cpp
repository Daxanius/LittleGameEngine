#include "AudioManager.h"
#include "AudioPlayer.h"

#include <iostream>

dae::AudioManager::AudioManager()
	: m_Running(true),
	m_Player(std::make_unique<AudioPlayer>()) {
	m_WorkerThread = std::thread(&AudioManager::ProcessQueue, this);
}

dae::AudioManager::~AudioManager() {
	m_Running = false;
	m_CondVar.notify_all();
	if (m_WorkerThread.joinable()) {
		m_WorkerThread.join();
	}
}

void dae::AudioManager::QueueCommand(const AudioCommand& command) {
	{
		std::lock_guard<std::mutex> lock(m_Mutex);
		m_CommandQueue.push_back(command);
	}
	m_CondVar.notify_one();
}

void dae::AudioManager::ProcessQueue() {
	while (m_Running) {
		AudioCommand cmd;

		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			m_CondVar.wait(lock, [&]() { return !m_CommandQueue.empty() || !m_Running; });

			if (!m_Running && m_CommandQueue.empty())
				break;

			cmd = std::move(m_CommandQueue.front());
			m_CommandQueue.pop_front();
		}

		// Process command
		std::visit([&](auto&& command) {
			using T = std::decay_t<decltype(command)>;
			if constexpr (std::is_same_v<T, PlayMusicCommand>) {
				m_Player->PlaySound(command.filepath);
			} else if constexpr (std::is_same_v<T, PlayChunkCommand>) {
				m_Player->PlayChunk(command.filepath);
			}
		}, cmd);
	}
}
