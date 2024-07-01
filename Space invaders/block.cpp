#include "block.hpp"

Block::Block(const Vector2& position)
	:m_position(position) {}

void Block::draw() {
	DrawRectangle(m_position.x, m_position.y, 3, 3, { 243, 216, 63, 255 });
}

Rectangle Block::get_rect() {
	return { m_position.x, m_position.y, 3, 3 };
}