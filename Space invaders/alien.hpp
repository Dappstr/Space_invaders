#pragma once

#include <raylib.h>
#include <array>

class Alien {
public:
	Alien(int type, const Vector2& position);
	void update(const int direction);
	void draw();
	int get_type();
	static void unload_images();
	Rectangle get_rect();

	static std::array<Texture2D, 3> m_alien_images;
	Texture2D m_image{};
	int m_type{};
	Vector2 m_position;
private:

};