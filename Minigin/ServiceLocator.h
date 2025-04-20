#pragma once

namespace dae {
	class AudioManager;

	class ServiceLocator {
	public:
		static void Provide(AudioManager* service) { m_AudioService = service; }
		static AudioManager* GetAudio() { return m_AudioService; }

	private:
		inline static AudioManager* m_AudioService = nullptr;
	};
}
