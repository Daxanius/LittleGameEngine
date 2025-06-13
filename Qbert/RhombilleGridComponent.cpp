#include "RhombilleGridComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"

dae::RhombilleGridComponent::RhombilleGridComponent(GameObject& pOwner, const std::string& texturePath, int tileWidth, int tileHeight, int rows, float scale) 
	: BaseComponent(pOwner), m_tileWidth(tileWidth), m_tileHeight(tileHeight), m_rows(rows), m_scale(scale), m_variant() {
	m_pTexture = ResourceManager::GetInstance().LoadTexture(texturePath);

	m_variant = 0;

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
			const auto worldPosition{ ToWorldPosition(row, col) };
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
	m_variant = variant;
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

std::pair<int, int> dae::RhombilleGridComponent::ToGridCoords(const glm::vec2& worldPos) const {
	const auto& gridWorldPosition{ GetOwner().GetLocalTransform().GetPosition() };

	const float dx = worldPos.x - gridWorldPosition.x;
	const float dy = worldPos.y - gridWorldPosition.y;

	// Recover row from y
	const float rowF = dy / (m_tileHeight * 0.75f * m_scale);
	const int row = static_cast<int>(std::round(rowF));

	// Plug row back into x equation to solve for col
	const float colF = (dx / (m_tileWidth * m_scale)) + (row * 0.5f);
	const int col = static_cast<int>(std::round(colF));

	return { row, col };
}

bool dae::RhombilleGridComponent::AreAllTilesState(int state) const {
	for (int row{}; row < m_rows; row++) {
		for (int col{}; col <= row; col++) {
			if (m_tiles[row][col].state != state) {
				return false;
			}
		}
	}

	return true;
}

void dae::RhombilleGridComponent::SetAllStates(int state) {
	for (int row{}; row < m_rows; row++) {
		for (int col{}; col <= row; col++) {
			m_tiles[row][col].state = state;
		}
	}
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

void dae::RhombilleGridComponent::GetRandomTile(int& row, int& col) const {
	int randomRow = rand() % m_rows;
	int randomCol = rand() % (randomRow + 1);
	row = randomRow;
	col = randomCol;
}

int dae::RhombilleGridComponent::GetRandomCol(int row) const {
    return rand() % (row + 1);
}

int dae::RhombilleGridComponent::GetRandomRow() const {
	return rand() % m_rows -1;
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

