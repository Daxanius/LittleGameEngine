#include "CoilyStateBall.h"
#include "CoilyComponent.h"
#include "hash.h"
#include "GridMovementComponent.h"
#include "CoilyStateSnake.h"
#include <random> 

dae::CoilyStateBall::CoilyStateBall(CoilyComponent* pCoilyComponent) : AbstractCoilyState(pCoilyComponent) {
	m_pGridMovementComponent = GetCoilyComponent()->GetOwner().GetComponent<GridMovementComponent>();
	assert(m_pGridMovementComponent != nullptr);

	m_pSpriteComponent = GetCoilyComponent()->GetOwner().GetComponent<SpriteComponent>();
	assert(m_pSpriteComponent != nullptr);

	m_pGridNavigationComponent = GetCoilyComponent()->GetOwner().GetComponent<GridNavigationComponent>();
	assert(m_pGridNavigationComponent != nullptr);

	m_pCoilyBallMovementObserver = std::make_shared<CoilyBallMovementObserver>(pCoilyComponent);
}

void dae::CoilyStateBall::OnEnter() {
	m_pSpriteComponent->SetState(make_sdbm_hash("ball_idle"));

	int maxRow = m_pGridMovementComponent->GetRhombilleGrid()->GetRows() -1;

	int randomCol = m_pGridMovementComponent->GetRhombilleGrid()->GetRandomCol(maxRow);

	m_pGridMovementComponent->GetSubject().AddObserver(m_pCoilyBallMovementObserver);

	m_pGridNavigationComponent->SetTarget(maxRow, randomCol);
	m_pGridNavigationComponent->Enable();
}

void dae::CoilyStateBall::Update(float) {
	if (m_pGridMovementComponent->HasArrived()) {
		GetCoilyComponent()->GetSubject().Notify("ball_jump");
	}

	int ownRow{ m_pGridMovementComponent->GetRow() };

	if (ownRow >= GetCoilyComponent()->GetLevel()->GetRhombilleGrid()->GetRows() - 1) {
		GetCoilyComponent()->SetState(std::make_shared<CoilyStateSnake>(GetCoilyComponent()));
	}
}

void dae::CoilyStateBall::OnExit() {
	m_pGridNavigationComponent->Disable();

	m_pGridMovementComponent->GetSubject().RemoveObserver(m_pCoilyBallMovementObserver);
}
