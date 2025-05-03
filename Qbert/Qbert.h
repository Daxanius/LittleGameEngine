#pragma once
#include <memory>
#include "Singleton.h"
#include "SoundObserver.h"
#include "Font.h"

namespace dae {
	class Scene;

	class Qbert : public Singleton<Qbert> {
	public:
		Qbert();

		Qbert(const Qbert&) = delete;
		Qbert& operator=(const Qbert&) = delete;
		Qbert(Qbert&&) = delete;
		Qbert& operator=(Qbert&&) = delete;
		~Qbert() = default;
	private:
		void CreateLevelScene();
		void CreateMenuScene();

		std::shared_ptr<Scene> m_pLevelScene;
		std::shared_ptr<Scene> m_pMenuScene;

		std::shared_ptr<Font> m_pFont;

		std::shared_ptr<SoundObserver> m_pSoundObserver;
	};
}
