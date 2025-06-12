#include "ScoreboardScene.h"
#include "InputManager.h"
#include "ChangeSceneCommand.h"
#include "Qbert.h"
#include "TextComponent.h"
#include <memory>
#include <iomanip>
#include <sstream>

dae::ScoreboardScene::ScoreboardScene(int scoresToDisplay) 
 : Scene("Scoreboard"), m_scoresToDisplay(scoresToDisplay) {
}

void dae::ScoreboardScene::OnSetup() {
	auto scoreboardTextObject{ std::make_unique<GameObject>(Transform{ (640 / 2) - 120, 50 }) };
	scoreboardTextObject->AddComponent<TextComponent>("Scoreboard", Qbert::GetInstance().GetFontLarge());

	auto scoreboardObject{ std::make_unique<GameObject>(Transform{ (640 / 2) - 80, 75 }) };
	m_pParagraphComponent = scoreboardObject->AddComponent<ParagraphComponent>("", Qbert::GetInstance().GetFontMedium());

	auto backTextObject{ std::make_unique<GameObject>(Transform{ (640 / 2) - 170, 425 }) };
	backTextObject->AddComponent<TextComponent>("Press ESCAPE or B to go back", Qbert::GetInstance().GetFontSmall());

	Add(std::move(scoreboardTextObject));
	Add(std::move(scoreboardObject));
	Add(std::move(backTextObject));
}

void dae::ScoreboardScene::OnEnter() {
	InputManager::GetInstance().ClearAllBindings();

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Escape, Keyboard::ActionType::Release },
		std::move(std::make_unique<ChangeSceneCommand>("Menu"))
	);

	InputManager::GetInstance().BindKeyboardCommand(
		Keyboard::KeyState{ Keyboard::Key::Enter, Keyboard::ActionType::Release },
		std::move(std::make_unique<ChangeSceneCommand>("Menu"))
	);

	UpdateScoreText();
}

void dae::ScoreboardScene::UpdateScoreText() {
	if (m_pParagraphComponent == nullptr) {
		return;
	}

	const auto& scores{ Qbert::GetInstance().GetScoreInfo() };
	std::ostringstream oss;

	for (int index = 0; index < m_scoresToDisplay; ++index) {
		oss << "\n";

		if (index >= static_cast<int>(scores.size())) {
			oss << "___ 00000";
		} else {
			const Score& score = scores[index];

			std::string name = score.name.substr(0, 3);
			for (char& c : name) c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));

			oss << std::setw(3) << std::left << name << " "
					<< std::setw(5) << std::setfill('0') << std::right << score.score;
		}
	}

	m_pParagraphComponent->SetText(oss.str());
}

