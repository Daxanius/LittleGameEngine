#pragma once  
#include "BaseComponent.h"  
#include "GameObject.h"
#include "AbstractCoilyState.h"
#include "GridMovementComponent.h"
#include "GridNavigationComponent.h"
#include "LevelComponent.h"
#include <memory>

namespace dae {  
	class CoilyComponent : public BaseComponent {
	public:  
		CoilyComponent(GameObject& pOwner, LevelComponent* pLevelComponent);

		void SetState(std::shared_ptr<AbstractCoilyState> pState);

		LevelComponent* GetLevel() const;

		void FixedUpdate() override {};
		void Update(float deltaTime) override;  
		void PostUpdate() override {};
		void Render() override {};
	private: 
		std::shared_ptr<AbstractCoilyState> m_pCurrentState;

		GridMovementComponent* m_pOwnMovementComponent{};
		LevelComponent* m_pLevelComponent{};
	};
}
