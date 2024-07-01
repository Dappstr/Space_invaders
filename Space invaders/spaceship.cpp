#pragma once
#include "spaceship.hpp"

Space_ship::Space_ship() {
	m_image = LoadTexture("Graphics/spaceship.png");
	m_position.x = (GetScreenWidth() - m_image.width) / 2;
	m_position.y = GetScreenHeight() - m_image.height - 100;
	m_last_fire_time = 0;
	m_laser_sound = LoadSound("Sounds/laser.ogg");
}

void Space_ship::draw() {
	DrawTextureV(m_image, m_position, WHITE);
}

void Space_ship::move_left() {
	m_position.x -= 7;
	if (m_position.x < 25) {
		m_position.x = 25;
	}
}

void Space_ship::move_right() {
	m_position.x += 7;
	if (m_position.x > GetScreenWidth() - m_image.width - 25) {
		m_position.x = GetScreenWidth() - m_image.width - 25;
	}
}

void Space_ship::fire_laser() {
	if (GetTime() - m_last_fire_time >= 0.35) {
		m_lasers.emplace_back(std::move(Laser({ m_position.x + m_image.width / 2 - 2,m_position.y }, -6)));
		m_last_fire_time = GetTime();
		PlaySound(m_laser_sound);
	}
}

Rectangle Space_ship::get_rect() {
	return { m_position.x, m_position.y, static_cast<float>(m_image.width), static_cast<float>(m_image.height)};
}

void Space_ship::reset() {
	m_position.x = (GetScreenWidth() - m_image.width) / 2.0f;
	m_position.y = GetScreenHeight() - m_image.height - 100;
	m_lasers.clear();
}

Space_ship::~Space_ship() {
	UnloadTexture(m_image);
	UnloadSound(m_laser_sound);
}