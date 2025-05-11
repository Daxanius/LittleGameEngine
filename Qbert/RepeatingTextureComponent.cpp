#include "RepeatingTextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::RepeatingTextureComponent::RepeatingTextureComponent(GameObject& pOwner, const std::string& texturePath, int textureWidth, int textureHeight, int textureOffsetX, int textureOffsetY, float padding, float scale)
: BaseComponent(pOwner), m_textureWidth(textureWidth), m_textureHeight(textureHeight), m_textureOffsetX(textureOffsetX), m_textureOffsetY(textureOffsetY), m_padding(padding), m_scale(scale) {
	m_pTexture = ResourceManager::GetInstance().LoadTexture(texturePath);
}

void dae::RepeatingTextureComponent::SetRows(int rows) {
	if (rows < 0) {
		return;
	}

	m_rows = rows;
}

void dae::RepeatingTextureComponent::SetCols(int cols) {
	if (cols < 0) {
		return;
	}

	m_cols = cols;
}

void dae::RepeatingTextureComponent::Render() {
	if (!m_pTexture) return;

	const auto& worldPos = GetOwner().GetWorldTransform().GetPosition();

	for (int row = 0; row < m_rows; ++row) {
		for (int col = 0; col < m_cols; ++col) {
			float x = worldPos.x + col * (m_textureWidth * m_scale + m_padding);
			float y = worldPos.y + row * (m_textureHeight * m_scale + m_padding);

			Renderer::GetInstance().RenderTexture(
				*m_pTexture,
				x, y,
				static_cast<float>(m_textureWidth) * m_scale,
				static_cast<float>(m_textureHeight) * m_scale,
				m_textureOffsetX,
				m_textureOffsetY,
				m_textureWidth,
				m_textureHeight
			);
		}
	}
}
