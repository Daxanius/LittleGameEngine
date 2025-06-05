#include "RhombilleGridAnimationComponent.h"
#include "hash.h"

dae::RhombilleGridAnimationComponent::RhombilleGridAnimationComponent(GameObject& pOwner, float animationDuration, int repetitions)
	: BaseComponent(pOwner), m_animationDuration(animationDuration), m_repetitions(repetitions)
{
	m_pRhombilleGridComponent = GetOwner().GetComponent<RhombilleGridComponent>();
	m_pLevelComponent = GetOwner().GetComponent<LevelComponent>();
}

void dae::RhombilleGridAnimationComponent::Update(float deltaTime) {
	if (!m_playing) {
		return;
	}

	if (m_currentTimeLeft <= 0.f) {
		m_playing = false;
		m_pLevelComponent->UnpauseLevel();
		m_pRhombilleGridComponent->SetAllStates(0);
		m_pRhombilleGridComponent->SetVariant(m_pLevelComponent->GetRound());
		m_currentTimeLeft = 0.f;

		m_Subject.Notify(dae::Event{ make_sdbm_hash("grid_animation_done") });
		return;
	}

	float progress{ 1.f - (m_currentTimeLeft / m_animationDuration) };
	m_currentState = static_cast<int>(progress * m_repetitions * 3.f) % 3;
	m_pRhombilleGridComponent->SetAllStates(m_currentState);
	m_currentTimeLeft -= deltaTime;
}

void dae::RhombilleGridAnimationComponent::PlayAnimation() {
	m_currentState = 0;
	m_currentTimeLeft = m_animationDuration;
	m_originalState = m_pRhombilleGridComponent->GetTile(0,0)->state;
	m_playing = true;
	m_pLevelComponent->PauseLevel();
}

bool dae::RhombilleGridAnimationComponent::IsPlaying() const {
	return m_playing;
}
