#pragma once
#include "Command.h"
#include "ServiceLocator.h"
#include "AbstractSoundSystem.h"
#include <string>

namespace dae {
	class PlaySoundCommand : public Command {
	public:
		PlaySoundCommand(const std::string& file, float volume);

		void Execute() override;
	private:
		SoundId m_soundId{};
		float m_volume{ 1.f };
	};
}