#pragma once

#include <raylib.h>

class Mystery_ship {
public:
	Mystery_ship();
	void update();
	void draw();
	void spawn();
	Rectangle get_rect();
	~Mystery_ship();
	bool m_alive;

private:
	Vector2 m_position;
	Texture2D m_image;
	int speed;
};