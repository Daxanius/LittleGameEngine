#include "SelectionMenuComponent.h"
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "hash.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include <algorithm>

dae::SelectionMenuComponent::SelectionMenuComponent(GameObject& pOwner, std::shared_ptr<Font> font, const Color& color, int padding, std::shared_ptr<Texture2D> pSelectionArrowTexture) : BaseComponent(pOwner), m_Color(color), m_pFont(font), m_padding(padding), m_pSelectionArrowTexture(pSelectionArrowTexture), m_subject() {
}

void dae::SelectionMenuComponent::AddOption(Option&& option) {
	// Add command to the list
	m_optionCommands.emplace_back(std::move(option.command));

	// Get the texture and compute which texture is the widest
	auto texture{ CreateTextureFromText(option.text) };
	m_widestWidth = std::max(texture->GetSize().x, m_widestWidth);
	m_optionTextures.emplace_back(texture);
}

void dae::SelectionMenuComponent::NextOption() {
	m_currentOption = (m_currentOption + 1) % static_cast<int>(m_optionCommands.size());
	Event event{ make_sdbm_hash("menu_next") };
	m_subject.Notify(event);
}

void dae::SelectionMenuComponent::PreviousOption() {
	m_currentOption = m_currentOption - 1 < 0 ? static_cast<int>(m_optionCommands.size()) - 1 : m_currentOption - 1;
	Event event{ make_sdbm_hash("menu_previous") };
	m_subject.Notify(event);
}

void dae::SelectionMenuComponent::ConfirmOption() {
	if (m_currentOption >= 0 && m_currentOption < static_cast<int>(m_optionCommands.size())) {
		m_optionCommands[m_currentOption]->Execute();

		Event event{ make_sdbm_hash("menu_confirm") };
		m_subject.Notify(event);
	}
}

void dae::SelectionMenuComponent::Render() {
	glm::vec3 position{ GetOwner().GetWorldTransform().GetPosition() };

	const float arrowOffset = 10.0f; // Padding between arrow and text

	for (size_t i = 0; i < m_optionTextures.size(); ++i) {
		const auto& texture = m_optionTextures[i];
		const auto size = texture->GetSize();

		// Calculate horizontal centering offset for the text
		const float xOffset = static_cast<float>(m_widestWidth - size.x) / 2.0f;

		// Draw the selection arrow if this is the current option
		if (static_cast<int>(i) == m_currentOption && m_pSelectionArrowTexture) {
			const float arrowX = position.x - size.y - arrowOffset;
			Renderer::GetInstance().RenderTexture(*m_pSelectionArrowTexture, arrowX, position.y, static_cast<float>(size.y), static_cast<float>(size.y));
		}

		// Draw the option text centered
		Renderer::GetInstance().RenderTexture(*texture, position.x + xOffset, position.y);
		position.y += size.y + m_padding;
	}
}

dae::Subject& dae::SelectionMenuComponent::GetSubject() {
	return m_subject;
}

std::shared_ptr<dae::Texture2D> dae::SelectionMenuComponent::CreateTextureFromText(const std::string& text) {
	const SDL_Color color = { static_cast<Uint8>(m_Color.R), static_cast<Uint8>(m_Color.G), static_cast<Uint8>(m_Color.B), static_cast<Uint8>(m_Color.A) };
	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), text.c_str(), color);
	if (surf == nullptr) {
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}

	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr) {
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}

	SDL_FreeSurface(surf);
	return std::make_shared<Texture2D>(texture);
}
