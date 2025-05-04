#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include <memory>
#include <unordered_map>
#include "GameObject.h"

namespace dae {
	using StateId = unsigned int;

	class SpriteComponent : public BaseComponent {
	public:
		SpriteComponent(GameObject& pOwner, const std::string& texturePath, int frameWidth, int frameHeight, float scale = 1.f);

		struct State {
			int offset;
			int frames;
			int fps;
		};

		void FixedUpdate() override {};
		void PostUpdate() override {};
		void Update(float deltaTime) override;
		void Render() override;

		void AddState(StateId stateId, State state);
		void SetState(StateId stateId);
	private:
		float m_elapsedTime{};
		float m_scale{};

		int m_frameWidth{};
		int m_frameHeight{};

		int m_frame{};

		// The actual texture of the spritesheet
		std::shared_ptr<Texture2D> m_pTexture;
		std::unordered_map<StateId, State> m_states;

		StateId m_currentState{};
	};
}