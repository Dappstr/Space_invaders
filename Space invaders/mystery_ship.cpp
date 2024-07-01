#include "mystery_ship.hpp"

Mystery_ship::Mystery_ship() {
	m_image = LoadTexture("Graphics/mystery.png");
	m_alive = false;
}
void Mystery_ship::update() {
	if (m_alive) {
		m_position.x += speed;
		if (m_position.x > GetScreenWidth() - m_image.width - 25 || m_position.x < 25) {
			m_alive = false;
		}
	}
}

void Mystery_ship::draw() {
	if (m_alive) {
		DrawTextureV(m_image, m_position, WHITE);
	}
}

void Mystery_ship::spawn() {
	m_position.y = 90;

	int side = GetRandomValue(0, 1);
	
	if (side == 0) {
		m_position.x = 25;
		speed = 3;
	}
	else {
		m_position.x = GetScreenWidth() - m_image.width - 25;
		speed = -3;
	}
	m_alive = true;
}

Rectangle Mystery_ship::get_rect() {
	if (m_alive) {
		return { m_position.x, m_position.y,
				static_cast<float>(m_image.width),
				static_cast<float>(m_image.height) };
	}
	else {
		return { m_position.x, m_position.y, 0, 0 };
	}
}

Mystery_ship::~Mystery_ship() {
	UnloadTexture(m_image);
}