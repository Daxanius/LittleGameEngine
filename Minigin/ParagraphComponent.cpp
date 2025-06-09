#include "ParagraphComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include <sstream>

dae::ParagraphComponent::ParagraphComponent(GameObject& pOwner, const std::string& text, std::shared_ptr<Font> font, float lineSpacing)
 : BaseComponent(pOwner), m_needsUpdate(true), m_Text(text), m_pFont(std::move(font)), m_lineSpacing(lineSpacing) {
}

void dae::ParagraphComponent::Update(float) {
    if (!m_needsUpdate) return;

    m_lineTextures.clear();
    std::istringstream stream(m_Text);
    std::string line;
    const SDL_Color color = { 255, 255, 255, 255 };

    while (std::getline(stream, line)) {
				// Line normalization
			  if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (line.empty()) line = " "; // Ensure empty lines still generate textures

        SDL_Surface* surf = TTF_RenderText_Blended(m_pFont->GetFont(), line.c_str(), color);
        if (!surf) {
            throw std::runtime_error("Render text failed: " + std::string(SDL_GetError()));
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
        if (!texture) {
            SDL_FreeSurface(surf);
            throw std::runtime_error("Create text texture from surface failed: " + std::string(SDL_GetError()));
        }

        SDL_FreeSurface(surf);
        m_lineTextures.push_back(std::make_shared<Texture2D>(texture));
    }

    m_needsUpdate = false;
}

void dae::ParagraphComponent::Render() {
	  const auto& position = GetOwner().GetWorldTransform().GetPosition();
    float yOffset = 0.0f;

    for (const auto& texture : m_lineTextures) {
        if (texture) {
            Renderer::GetInstance().RenderTexture(*texture, position.x, position.y + yOffset);
            yOffset += texture->GetSize().y + m_lineSpacing;
        }
    }
}

void dae::ParagraphComponent::SetText(const std::string& text) {
    if (m_Text != text) {
        m_Text = text;
        m_needsUpdate = true;
    }
}
