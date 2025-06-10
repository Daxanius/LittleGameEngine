#include "TextInputComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

dae::TextInputComponent::TextInputComponent(GameObject& pOwner, int stringSize, std::shared_ptr<Font> font, int characterSpacing)
 : BaseComponent(pOwner), m_stringSize(stringSize), m_font(font), m_characterSpacing(characterSpacing) {
	m_values.resize(m_stringSize);
}

void dae::TextInputComponent::Update(float) {
	m_textValue.clear();
	m_characterTextures.clear();

	for (int c : m_values) {
		char character{ AVAILABLE_CHARACTERS[c] };
		m_textValue.push_back(character);

		// Generate texture
		std::string charStr(1, character);
		const SDL_Color color = { 255,255,255,255 };
		SDL_Surface* surf = TTF_RenderText_Blended(m_font->GetFont(), charStr.c_str(), color);
		if (!surf) throw std::runtime_error("Failed to render character: " + std::string(SDL_GetError()));
		
		SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		SDL_FreeSurface(surf);
		if (!texture) throw std::runtime_error("Failed to create texture: " + std::string(SDL_GetError()));

		m_characterTextures.push_back(std::make_shared<Texture2D>(texture));
	}

	m_needsUpdate = false;
}

void dae::TextInputComponent::Render() {
	const auto& position{ GetOwner().GetWorldTransform().GetPosition() };

	for (size_t i = 0; i < m_characterTextures.size(); ++i) {
		const auto& texture = m_characterTextures[i];
		if (texture) {
			Renderer::GetInstance().RenderTexture(*texture, position.x + int(i) * m_characterSpacing, position.y);
		}
	}

	// Render caret below the current character
	if (!m_caretTexture) {
		const SDL_Color color = { 255,255,255,255 };
		SDL_Surface* surf = TTF_RenderText_Blended(m_font->GetFont(), "^", color);
		if (!surf) throw std::runtime_error("Failed to render caret: " + std::string(SDL_GetError()));

		SDL_Texture* tex = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		SDL_FreeSurface(surf);
		if (!tex) throw std::runtime_error("Failed to create caret texture: " + std::string(SDL_GetError()));

		m_caretTexture = std::make_shared<Texture2D>(tex);
	}

	const int caretYOffset = 30;
	Renderer::GetInstance().RenderTexture(*m_caretTexture, position.x + m_characterIndex * m_characterSpacing, position.y + caretYOffset);
}

void dae::TextInputComponent::Left() {
	m_characterIndex = (m_characterIndex - 1 + m_stringSize) % m_stringSize;
}

void dae::TextInputComponent::Right() {
	m_characterIndex = (m_characterIndex + 1) % m_stringSize;
}

void dae::TextInputComponent::Up() {
	int& val = m_values[m_characterIndex];
	val = (val + 1) % static_cast<int>(AVAILABLE_CHARACTERS.length());
	m_needsUpdate = true;
}

void dae::TextInputComponent::Down() {
	int& val = m_values[m_characterIndex];
	val = (val - 1 + static_cast<int>(AVAILABLE_CHARACTERS.length())) % static_cast<int>(AVAILABLE_CHARACTERS.length());
	m_needsUpdate = true;
}

const std::string& dae::TextInputComponent::GetValue() {
	return m_textValue;
}
