#include "TextComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

dae::TextComponent::TextComponent(GameObject& pOwner, const std::string& text, std::shared_ptr<Font> font)
	: BaseComponent(pOwner), m_needsUpdate(true), m_Text(text), m_pFont(std::move(font)), m_textTexture(nullptr)
{ 
}

void dae::TextComponent::Update(float) {
	if (m_needsUpdate) {
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
		m_textTexture = std::make_shared<Texture2D>(texture);
		m_needsUpdate = false;
	}
}

void dae::TextComponent::Render() {
	if (m_textTexture) {
		const auto& position{ GetOwner().GetWorldTransform().GetPosition() };
		Renderer::GetInstance().RenderTexture(*m_textTexture, position.x, position.y);
	}
}

// This implementation uses the "dirty flag" pattern
void dae::TextComponent::SetText(const std::string& text) {
	if (m_Text != text) {
		m_Text = text;
		m_needsUpdate = true;
	}
}
