#pragma once
#include "GameObject.h"

namespace dae {
	class Command {
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;
	};

	class ActorCommand : Command {
	protected:
		ActorCommand(GameObject* actor);

		GameObject* GetActor() const;

	private:
		GameObject* m_Actor{ nullptr };
	};
}