#include "CoilyStateBall.h"
#include "CoilyComponent.h"
#include "hash.h"
#include "GridMovementComponent.h"
#include <random> 

dae::CoilyStateBall::CoilyStateBall(CoilyComponent* pCoilyComponent) : AbstractCoilyState(pCoilyComponent) {
	m_pGridMovementComponent = GetCoilyComponent()->GetOwner().GetComponent<GridMovementComponent>();
	assert(m_pGridMovementComponent != nullptr);

	m_pSpriteComponent = GetCoilyComponent()->GetOwner().GetComponent<SpriteComponent>();
	assert(m_pSpriteComponent != nullptr);

	m_pGridNavigationComponent = GetCoilyComponent()->GetOwner().GetComponent<GridNavigationComponent>();
	assert(m_pGridNavigationComponent != nullptr);
}

void dae::CoilyStateBall::OnEnter() {
	m_pSpriteComponent->SetState(make_sdbm_hash("ball"));

	int maxRow = m_pGridMovementComponent->GetRhombilleGrid()->GetRows();

	// Random engine - static to avoid re-seeding every time
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, maxRow);

	int randomCol = dist(gen); // Value in [0, maxRow]

	m_pGridNavigationComponent->SetTarget(maxRow, randomCol);
	m_pGridNavigationComponent->Enable();
}

void dae::CoilyStateBall::Update(float) {
}

void dae::CoilyStateBall::OnExit() {
	m_pGridNavigationComponent->Disable();
}
