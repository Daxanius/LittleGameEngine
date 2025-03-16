#pragma once
#include "Command.h"
#include "ScoreComponent.h"

namespace dae {
	class IncreaseScoreCommand : public ActorCommand {
	public:
		IncreaseScoreCommand(GameObject* actor, int amount);

		void Execute() override;
	private:
		int m_amount;

		ScoreComponent* m_pScoreComponent;
	};
}

