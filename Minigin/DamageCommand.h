#pragma once
#include "Command.h"
#include "HealthComponent.h"

namespace dae {
	class DamageCommand : public ActorCommand {
	public:
		DamageCommand(GameObject* actor, int amount);

		void Execute() override;
	private:
		int m_amount;

		HealthComponent* m_pHealthComponent;
	};
}

