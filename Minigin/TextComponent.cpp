#include <stdexcept>
#include <SDL_ttf.h>
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

dae::TextComponent::TextComponent(GameObject& pOwner, const std::string& text, std::shared_ptr<Font> font)
	: BaseComponent(pOwner), m_NeedsUpdate(true), m_Text(text), m_pFont(std::move(font)), m_TextTexture(nullptr)
{ 
	m_pTransformComponent = GetOwner().GetComponent<TransformComponent>();
	assert(m_pTransformComponent); // A transform should exist for this component
}

void dae::TextComponent::Update(float) {
	if (m_NeedsUpdate && m_pTransformComponent) {
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_TextTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::Render() const {
	if (m_TextTexture && m_pTransformComponent) {
		const auto& position{ m_pTransformComponent->GetPosition() };
		Renderer::GetInstance().RenderTexture(*m_TextTexture, position.x, position.y);
	}
}

void dae::TextComponent::PostUpdate() {
	// Just a basic null setting
	if (m_pTransformComponent->IsDestroyed()) {
		m_pTransformComponent = nullptr;
	}
}

// This implementation uses the "dirty flag" pattern
void dae::TextComponent::SetText(const std::string& text) {
	m_Text = text;
	m_NeedsUpdate = true;
}


