#pragma once
#include <raylib.h>

class Block {
public:
	Block(const Vector2& position);
	void draw();
	Rectangle get_rect();

private:
	Vector2 m_position;
};