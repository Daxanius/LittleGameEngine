#pragma once
#include <memory>
#include "Singleton.h"
#include "SoundObserver.h"
#include "Level.h"
#include "Score.h"
#include "Font.h"

namespace dae {
	class Scene;

	class Qbert : public Singleton<Qbert> {
	public:
		Qbert();

		void Start();

		std::shared_ptr<Font> GetFontLarge() const;
		std::shared_ptr<Font> GetFontMedium() const;
		std::shared_ptr<Font> GetFontSmall() const;
		std::shared_ptr<Font> GetFontVerySmall() const;
		std::shared_ptr<SoundObserver> GetSoundObserver() const;

		const std::vector<Level>& GetLevelInfo() const;
		const std::vector<Score>& GetScoreInfo() const;

		int GetLevelCount() const;

		void AddScore(const Score& score);

		Qbert(const Qbert&) = delete;
		Qbert& operator=(const Qbert&) = delete;
		Qbert(Qbert&&) = delete;
		Qbert& operator=(Qbert&&) = delete;
		~Qbert() = default;
	private:
		std::shared_ptr<Font> m_pFontLarge;
		std::shared_ptr<Font> m_pFontMedium;
		std::shared_ptr<Font> m_pFontSmall;
		std::shared_ptr<Font> m_pFontVerySmall;

		std::shared_ptr<SoundObserver> m_pSoundObserver;

		std::vector<Level> m_levelInfo;
		std::vector<Score> m_scoreInfo;
	};
}
