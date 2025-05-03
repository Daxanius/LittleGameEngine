#include "RhombileGridComponent.h"
#include "Renderer.h"

dae::RhombileGridComponent::RhombileGridComponent(GameObject& owner, int rows, float tileWidth, float tileHeight)
	: BaseComponent(owner), m_rows(rows), m_tileWidth(tileWidth), m_tileHeight(tileHeight) {
	InitializeGrid();
}

void dae::RhombileGridComponent::InitializeGrid() {
	const glm::vec2 startPos = GetOwner().GetWorldTransform().GetPosition();

	m_tiles.resize(m_rows);

	for (int row = 0; row < m_rows; ++row) {
		m_tiles[row].resize(row + 1);

		for (int col = 0; col <= row; ++col) {
			float x = startPos.x + (col - row * 0.5f) * m_tileWidth;
			float y = startPos.y + row * m_tileHeight;
			m_tiles[row][col].worldPos = { x, y };
		}
	}
}

const dae::Tile* dae::RhombileGridComponent::GetTile(int row, int col) const {
	if (row >= 0 && row < m_rows && col >= 0 && col <= row) {
		return &m_tiles[row][col];
	}
	return nullptr;
}

glm::vec2 dae::RhombileGridComponent::GetWorldPosition(int row, int col) const {
	const auto* tile = GetTile(row, col);
	return tile ? tile->worldPos : glm::vec2{};
}

std::pair<int, int> dae::RhombileGridComponent::WorldToGrid(const glm::vec2& worldPos) {
	glm::vec2 origin = GetOwner().GetWorldTransform().GetPosition();

	// Estimate row based on vertical distance
	float deltaY = worldPos.y - origin.y;
	int row = static_cast<int>(std::round(deltaY / m_tileHeight));

	if (row < 0 || row >= m_rows) return { -1, -1 };

	// Estimate column based on horizontal offset
	float expectedRowOffset = origin.x - (row * 0.5f * m_tileWidth);
	float deltaX = worldPos.x - expectedRowOffset;
	int col = static_cast<int>(std::round(deltaX / m_tileWidth));

	if (col < 0 || col > row) return { -1, -1 };

	return { row, col };
}

void dae::RhombileGridComponent::Render() {
#ifdef _DEBUG
	for (const auto& row : m_tiles) {
		for (const auto& tile : row) {
			if (tile.active) {
				// Renderer::GetInstance().RenderRect(tile.worldPos.x, tile.worldPos.y, m_tileWidth / 4.f, m_tileHeight / 4.f, { 255, 255, 0, 255 });
			}
		}
	}
#endif
}
