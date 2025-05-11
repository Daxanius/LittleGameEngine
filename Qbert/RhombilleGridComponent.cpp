#include "RhombilleGridComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"

dae::RhombilleGridComponent::RhombilleGridComponent(GameObject& pOwner, const std::string& texturePath, int tileWidth, int tileHeight, int rows, float scale) 
	: BaseComponent(pOwner), m_tileWidth(tileWidth), m_tileHeight(tileHeight), m_rows(rows), m_scale(scale), m_variant() {
	m_pTexture = ResourceManager::GetInstance().LoadTexture(texturePath);

	m_variant = 1;

	m_tiles.reserve(rows);

	// Fill the qbert grid
	for (int row{}; row < rows; row++) {
		m_tiles.emplace_back();
		m_tiles[row].reserve(row + 1);

		for (int col{}; col <= row; col++) {
			m_tiles[row].emplace_back(Tile{});
		}
	}
}

void dae::RhombilleGridComponent::Render() {
	for (int row = 0; row < static_cast<int>(m_tiles.size()); ++row) {
		int tilesInRow{ static_cast<int>(m_tiles[row].size()) };

		for (int col = 0; col < tilesInRow; ++col) {
			auto worldPosition{ ToWorldPosition(row, col) };
			Tile tile{ m_tiles[row][col] };

			Renderer::GetInstance().RenderTexture(
				*m_pTexture, 
				worldPosition.x,
				worldPosition.y,
				static_cast<float>(m_tileWidth) * m_scale, 
				static_cast<float>(m_tileHeight) * m_scale, 
				m_tileWidth * m_variant, m_tileHeight * tile.state, 
				m_tileWidth,
				m_tileHeight
			);
		}
	}
}

void dae::RhombilleGridComponent::SetVariant(int variant) {
	if (m_variant > 0) {
		m_variant = variant;
	}
}

int dae::RhombilleGridComponent::GetVariant() const {
	return m_variant;
}

glm::vec2 dae::RhombilleGridComponent::ToWorldPosition(int row, int col) {
	const auto& gridWorldPosition{ GetOwner().GetWorldTransform().GetPosition() };

	glm::vec2 worldPosition{
		gridWorldPosition.x + (col - row * 0.5f) * m_tileWidth * m_scale,
		gridWorldPosition.y + row * (m_tileHeight * 0.75f) * m_scale
	};

	return worldPosition;
}

dae::Tile* dae::RhombilleGridComponent::GetTile(int row, int col) {
	if (row < 0 || row >= m_rows) {
		return nullptr;
	}

	auto& rowData{ m_tiles[row] };
	if (col < 0 || col >= static_cast<int>(rowData.size())) {
		return nullptr;
	}

	return &rowData[col];
}

int dae::RhombilleGridComponent::GetRows() const {
    return m_rows;
}

int dae::RhombilleGridComponent::GetTileWidth() const {
	return m_tileWidth;
}

int dae::RhombilleGridComponent::GetTileHeight() const {
	return m_tileHeight;
}

float dae::RhombilleGridComponent::GetScale() const {
	return m_scale;
}

