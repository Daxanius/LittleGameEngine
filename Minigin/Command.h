#pragma once
#include "GameObject.h"

namespace dae {
	class Command {
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;

		// Commands can be marked for deletion too, such that they will unbind themselves (useful for when objects get destroyed)
		void MarkToUnbind();

		bool IsUnbound() const;
	private:
		bool m_unbound{};
	};

	class ActorCommand : public Command {
	protected:
		ActorCommand(GameObject* actor);

		[[nodiscard]] GameObject* GetActor() const;

	private:
		GameObject* m_Actor{ nullptr };
	};
}