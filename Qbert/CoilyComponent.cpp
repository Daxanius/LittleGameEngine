#include "CoilyComponent.h"

dae::CoilyComponent::CoilyComponent(GameObject& pOwner) : BaseComponent(pOwner) {
}

void dae::CoilyComponent::SetState(std::shared_ptr<AbstractCoilyState> pState) {
	if (m_pCurrentState) {
		m_pCurrentState->OnExit();
	}
	m_pCurrentState = std::move(pState);
	if (m_pCurrentState) {
		m_pCurrentState->OnEnter();
	}
}

void dae::CoilyComponent::Update(float deltaTime) {
	m_pCurrentState->Update(deltaTime);
}