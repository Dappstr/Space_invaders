#pragma once

#include <raylib.h>

class Laser {
public:
	Laser(const Vector2& position, const int speed);
	void update();
	void draw() const;
	Rectangle get_rect();
	~Laser();
	bool m_active;

private:
	Vector2 m_position;
	int m_speed{};
};