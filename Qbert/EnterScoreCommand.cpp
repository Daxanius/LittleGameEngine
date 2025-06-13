#include "EnterScoreCommand.h"
#include "SceneManager.h"
#include "Qbert.h"

dae::EnterScoreCommand::EnterScoreCommand(int score, TextInputComponent* pTextInputComponent)
	: m_score(score), m_pTextInputComponent(pTextInputComponent) {
}

void dae::EnterScoreCommand::Execute() {
	if (!m_pTextInputComponent->IsDone()) {
		return;
	}

	Qbert::GetInstance().AddScore(Score{ m_pTextInputComponent->GetValue(), m_score});
	SceneManager::GetInstance().SetScene("Menu");
}
