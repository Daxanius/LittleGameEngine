#pragma once
#include "BaseComponent.h"
#include <vector>
#include <memory>

namespace dae {
	struct Tile {
		glm::vec2 worldPos;
		bool active = true;
		int state = 0; // e.g., color level, visit count, etc.
	};

	class RhombileGridComponent : public BaseComponent {
	public:
		RhombileGridComponent(GameObject& owner, int rows, float tileWidth, float tileHeight);

		void FixedUpdate() override {}
		void Update(float) override {}
		void Render() override;

		// Grid access
		const Tile* GetTile(int row, int col) const;
		glm::vec2 GetWorldPosition(int row, int col) const;
		int GetRowCount() const { return m_rows; }

		std::pair<int, int> WorldToGrid(const glm::vec2& worldPos);
	private:
		int m_rows;
		float m_tileWidth;
		float m_tileHeight;

		std::vector<std::vector<Tile>> m_tiles;

		void InitializeGrid();
	};
}
