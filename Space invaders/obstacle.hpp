#pragma once

#include <vector>
#include "block.hpp"

class Obstacle {
public:
	Obstacle(const Vector2& position);
	void draw();
	Vector2 m_position;
	std::vector<Block> m_blocks;
	static std::vector<std::vector<int>> m_grid;
private:

};