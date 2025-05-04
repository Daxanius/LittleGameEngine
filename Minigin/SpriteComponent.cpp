#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::SpriteComponent::SpriteComponent(GameObject& pOwner, const std::string& texturePath, int frameWidth, int frameHeight, float scale)
: BaseComponent(pOwner), m_frameWidth(frameWidth), m_frameHeight(frameHeight), m_scale(scale) {
	m_pTexture = ResourceManager::GetInstance().LoadTexture(texturePath);
}

void dae::SpriteComponent::Update(float deltaTime) {
	if (m_states.find(m_currentState) == m_states.end()) return;
	const State& state = m_states[m_currentState];

	m_elapsedTime += deltaTime;

	float secondsPerFrame = 1.0f / static_cast<float>(state.fps);

	if (m_elapsedTime >= secondsPerFrame) {
		++m_frame;

		if (m_frame >= state.frames) {
			m_frame = 0;
		}

		// allow leftover time to carry over
		m_elapsedTime -= secondsPerFrame;
	}
}

void dae::SpriteComponent::Render() {
	if (m_states.find(m_currentState) == m_states.end()) return;
	const auto& worldPosition{ GetOwner().GetWorldTransform().GetPosition() };
	const auto& state{ m_states[m_currentState] };
	
	Renderer::GetInstance().RenderTexture(
		*m_pTexture,
		worldPosition.x,
		worldPosition.y,
		m_frameWidth * m_scale,
		m_frameHeight * m_scale,
		m_frameWidth * m_frame + m_frameWidth * state.offset,
		0,
		m_frameWidth,
		m_frameHeight
		);
}

void dae::SpriteComponent::AddState(StateId stateId, State state) {
	m_states[stateId] = state;
}

void dae::SpriteComponent::SetState(StateId stateId) {
	if (m_states.find(stateId) != m_states.end()) {
		m_currentState = stateId;
		m_frame = 0; // Reset the frame when the state changed
	}
}
