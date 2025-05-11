#include "CoilyStateSnake.h"
#include "CoilyComponent.h"
#include "hash.h"

dae::CoilyStateSnake::CoilyStateSnake(CoilyComponent* pCoilyComponent, GridMovementComponent* pTargetMovement) : AbstractCoilyState(pCoilyComponent), m_pTargetMovementComponent(pTargetMovement) {
	m_pGridMovementComponent = GetCoilyComponent()->GetOwner().GetComponent<GridMovementComponent>();
	assert(m_pGridMovementComponent != nullptr);

	m_pSpriteComponent = GetCoilyComponent()->GetOwner().GetComponent<SpriteComponent>();
	assert(m_pSpriteComponent != nullptr);

	m_pGridNavigationComponent = GetCoilyComponent()->GetOwner().GetComponent<GridNavigationComponent>();
	assert(m_pGridNavigationComponent != nullptr);
}

void dae::CoilyStateSnake::OnEnter() {
	m_pSpriteComponent->SetState(make_sdbm_hash("snake"));
	m_pGridNavigationComponent->SetTarget(m_pTargetMovementComponent->GetRow(), m_pTargetMovementComponent->GetCol());
	m_pGridNavigationComponent->Enable();
}

void dae::CoilyStateSnake::Update(float) {
}

void dae::CoilyStateSnake::OnExit() {
	m_pGridNavigationComponent->Disable();
}
