#include "laser.hpp"

Laser::Laser(const Vector2& position, const int speed)
	:m_position(position), m_speed(speed) {
	m_active = true;
}

void Laser::update() {
	m_position.y += m_speed;
	if (m_active) {
		if (m_position.y > GetScreenHeight() - 100|| m_position.y < 25) {
			m_active = false;
		}
	}
}

void Laser::draw() const {
	if (m_active) {
		DrawRectangle(m_position.x, m_position.y, 4, 15, { 243, 216, 63, 255 });
	}
}

Rectangle Laser::get_rect() {
	return { m_position.x, m_position.y, 4, 15 };
}

Laser::~Laser() {
}