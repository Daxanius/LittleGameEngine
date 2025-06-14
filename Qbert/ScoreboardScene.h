#pragma once
#include <Scene.h>
#include "Score.h"
#include "ParagraphComponent.h"

namespace dae {
	class ScoreboardScene : public Scene {
	public:
		ScoreboardScene(int scoresToDisplay);

		virtual void OnSetup();
		virtual void OnEnter();

		void UpdateScoreText();


		ScoreboardScene(const ScoreboardScene&) = delete;
		ScoreboardScene& operator=(const ScoreboardScene&) = delete;
		ScoreboardScene(ScoreboardScene&&) = delete;
		ScoreboardScene& operator=(ScoreboardScene&&) = delete;
		~ScoreboardScene() = default;
	private:
		int m_scoresToDisplay;

		ParagraphComponent* m_pParagraphComponent{};
	};
}
