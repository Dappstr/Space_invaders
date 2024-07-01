#include "alien.hpp"

//Texture2D Alien::m_alien_images[3] = {};
std::array<Texture2D, 3> Alien::m_alien_images{};

Alien::Alien(int type, const Vector2& position)
	:m_type(type), m_position(position) {

	if (m_alien_images[type - 1].id == 0) {
		switch (type) {
			case 1:
				m_alien_images[0] = LoadTexture("Graphics/alien_1.png");
				break;
			case 2:
				m_alien_images[1] = LoadTexture("Graphics/alien_2.png");
				break;
			case 3:
				m_alien_images[2] = LoadTexture("Graphics/alien_3.png");
				break;
			default:
				m_alien_images[0] = LoadTexture("Graphics/alien_1.png");
				break;
		}
	}
}

void Alien::update(const int direction) {
	m_position.x += direction;
}

void Alien::draw() {
	DrawTextureV(m_alien_images[m_type - 1], m_position, WHITE);
}

int Alien::get_type() {
	return m_type;
}

Rectangle Alien::get_rect() {
	return { m_position.x, m_position.y,
		static_cast<float>(m_alien_images.at(m_type - 1).width),
		static_cast<float>(m_alien_images.at(m_type - 1).height) };
}

void Alien::unload_images() {
	for (size_t i = 0; i < 3; ++i) {
		UnloadTexture(m_alien_images[i]);
	}
}