#pragma once
#include "raylib.h"
#include "laser.hpp"
#include <vector>

class Space_ship {
public:
	Space_ship();
	void draw();
	void move_left();
	void move_right();
	void fire_laser();
	Rectangle get_rect();
	void reset();
	~Space_ship();
	std::vector<Laser> m_lasers{};

private:
	Texture2D m_image;
	Vector2 m_position;
	double m_last_fire_time;
	Sound m_laser_sound;
};