#pragma once
#include "Command.h"
#include "LivesComponent.h"

namespace dae {
	class KillCommand final : public ActorCommand {
	public:
		KillCommand(GameObject* actor, int amount);

		void Execute() override;
	private:
		int m_amount;

		LivesComponent* m_pHealthComponent;
	};
}

