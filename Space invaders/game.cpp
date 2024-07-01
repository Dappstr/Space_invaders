#include "game.hpp"
#include <fstream>
#include <iostream>

Game::Game() {
	m_music = LoadMusicStream("Sounds/music.ogg");
	m_explosion_sound = LoadSound("Sounds/explosion.ogg");
	PlayMusicStream(m_music);

	init_game();
}

void Game::draw() {
	m_space_ship.draw();

	for (const auto& laser : m_space_ship.m_lasers) {
		laser.draw();
	}

	for (auto& obstacle : m_obstacles) {
		obstacle.draw();
	}

	for (auto& alien : m_aliens) {
		alien.draw();
	}

	for (auto& laser : m_alien_lasers) {
		laser.draw();
	}

	m_mystery_ship.draw();
}

void Game::update() {
	if (m_run) {
		double current_time = GetTime();
		if (current_time - m_time_last_spawn > m_mystery_ship_spawn_interval) {
			m_mystery_ship.spawn();
			m_time_last_spawn = GetTime();
			m_mystery_ship_spawn_interval = GetRandomValue(10, 20);
		}

		for (auto& laser : m_space_ship.m_lasers) {
			laser.update();
		}
		move_aliens();
		alien_shoot_laser();

		for (auto& laser : m_alien_lasers) {
			laser.update();
		}

		delete_inactive_lasers();

		m_mystery_ship.update();

		check_for_collisions();
	}
	else {
		if (IsKeyDown(KEY_ENTER)) {
			reset();
			init_game();
		}
	}
}

void Game::handle_input() {
	if (m_run) {
		if (IsKeyDown(KEY_LEFT)) {
			m_space_ship.move_left();
		}
		else if (IsKeyDown(KEY_RIGHT)) {
			m_space_ship.move_right();
		}
		else if (IsKeyDown(KEY_SPACE)) {
			m_space_ship.fire_laser();
		}
	}
}

void Game::delete_inactive_lasers() {
	for (auto it = m_space_ship.m_lasers.begin(); it != m_space_ship.m_lasers.end();) {
		if (!it->m_active) {
			it = m_space_ship.m_lasers.erase(it);
		}
		else {
			++it;
		}
	}

	for (auto it = m_alien_lasers.begin(); it != m_alien_lasers.end();) {
		if (!it->m_active) {
			it = m_alien_lasers.erase(it);
		}
		else {
			++it;
		}
	}
}

std::vector<Obstacle> Game::create_obstacles() {
	size_t obstacle_width = Obstacle::m_grid.at(0).size() * 3;
	float gap = (GetScreenWidth() - (4 * obstacle_width)) / 5;

	for (size_t i = 0; i < 4; ++i) {
		float offset_x = (i + 1) * gap + i * obstacle_width;
		m_obstacles.emplace_back(Obstacle({ offset_x, float(GetScreenHeight() - 200) }));
	}
	return m_obstacles;
}

std::vector<Alien> Game::create_aliens() {
	for (size_t row = 0; row < 5; ++row) {
		for (size_t column = 0; column < 11; ++column) {

			size_t alien_type;
			if (row == 0) {
				alien_type = 3;
			}
			else if (row == 1 || row == 2) {
				alien_type = 2;
			}
			else {
				alien_type = 1;
			}

			float x = 75 + column * 55;
			float y = 110 + row * 55;
			m_aliens.emplace_back(Alien(alien_type,{x, y}));
		}
	}
	return m_aliens;
}

void Game::move_aliens() {
	for (auto& alien : m_aliens) {
		if (alien.m_position.x + alien.m_alien_images[alien.m_type - 1].width > GetScreenWidth() - 25) {
			m_aliens_direction = -1;
			move_down_aliens(4);
		}
		else if (alien.m_position.x < 25) {
			m_aliens_direction = 1;
			move_down_aliens(4);
		}
		alien.update(m_aliens_direction);
	}
}

void Game::move_down_aliens(const int distance) {
	for (auto& alien : m_aliens) {
		alien.m_position.y += distance;
	}
}

void Game::check_for_collisions() {
	// Spaceship lasers
	for (auto& laser : m_space_ship.m_lasers) {
		auto it = m_aliens.begin();
		while (it != m_aliens.end()) {
			if (CheckCollisionRecs(it->get_rect(), laser.get_rect())) {
				PlaySound(m_explosion_sound);
				if (it->m_type == 1) {
					m_score += 100;
				}
				else if (it->m_type == 2) {
					m_score += 200;
				}
				else if (it->m_type == 3) {
					m_score += 300;
				}
				it = m_aliens.erase(it);
				laser.m_active = false;
				check_for_high_score();
			}
			else {
				++it;
			}
		}

		for (auto& obstacle : m_obstacles) {
			auto it = obstacle.m_blocks.begin();
			while (it != obstacle.m_blocks.end()) {
				if (CheckCollisionRecs(it->get_rect(), laser.get_rect())) {
					it = obstacle.m_blocks.erase(it);
					laser.m_active = false;
				}
				else {
					++it;
				}
			}
		}
		if (CheckCollisionRecs(m_mystery_ship.get_rect(), laser.get_rect())) {
			PlaySound(m_explosion_sound);
			m_mystery_ship.m_alive = false;
			laser.m_active = false;
			m_score += 500;
			check_for_high_score();
		}
	}

	// Alien lasers
	for (auto& laser : m_alien_lasers) {
		if (CheckCollisionRecs(laser.get_rect(), m_space_ship.get_rect())) {
			laser.m_active = false;
			--m_lives;
			if (m_lives == 0) {
				game_over();
			}
		}

		for (auto& obstacle : m_obstacles) {
			auto it = obstacle.m_blocks.begin();
			while (it != obstacle.m_blocks.end()) {
				if (CheckCollisionRecs(it->get_rect(), laser.get_rect())) {
					it = obstacle.m_blocks.erase(it);
					laser.m_active = false;
				}
				else {
					++it;
				}
			}
		}
	}

	for (auto& alien : m_aliens) {
		for (auto& obstacle : m_obstacles) {
			auto it = obstacle.m_blocks.begin();
			while (it != obstacle.m_blocks.end()) {
				if (CheckCollisionRecs(it->get_rect(), alien.get_rect())) {
					it = obstacle.m_blocks.erase(it);
				}
				else {
					++it;
				}
			}
		}
		if (CheckCollisionRecs(alien.get_rect(), m_space_ship.get_rect())) {
			game_over();
		}
	}
}

void Game::alien_shoot_laser() {
	double current_time = GetTime();
	if (current_time - m_time_last_alien_fired >= m_alien_laser_shoot_interval && !m_aliens.empty()) {
		int random_index = GetRandomValue(0, m_aliens.size() - 1);
		Alien& alien = m_aliens.at(random_index);
		m_alien_lasers.emplace_back(Laser({ alien.m_position.x + alien.m_alien_images.at(alien.m_type - 1).width / 2,
											alien.m_position.y + alien.m_alien_images.at(alien.m_type - 1).height }, 6));
		m_time_last_alien_fired = GetTime();
	}
}

void Game::game_over() {
	m_run = false;
}

void Game::reset() {
	m_space_ship.reset();
	m_aliens.clear();
	m_alien_lasers.clear();
	m_obstacles.clear();
}

void Game::init_game() {
	m_obstacles = create_obstacles();
	m_aliens = create_aliens();
	m_aliens_direction = 1;
	m_time_last_alien_fired = 0;
	m_time_last_spawn = 0.0;
	m_mystery_ship_spawn_interval = GetRandomValue(10, 20);
	m_lives = 3;
	m_score = 0;
	m_high_score = load_high_score_from_file();
	m_run = true;
}

void Game::check_for_high_score() {
	if (m_score > m_high_score) {
		m_high_score = m_score;
		save_high_score_to_file(m_high_score);
	}
}

void Game::save_high_score_to_file(const int high_score) {
	std::fstream file ("highscore.txt", std::ios::out | std::ios::trunc);
	file << high_score;
	file.close();
}

size_t Game::load_high_score_from_file() {
	std::fstream file ("highscore.txt", std::ios::in);
	size_t score{};
	if (file.is_open()) {
		file >> score;
		file.close();
	}
	else {
		std::cerr << "Failed to load highscore from file.";
	}
	return score;
}

Game::~Game() {
	Alien::unload_images();
	UnloadMusicStream(m_music);
	UnloadSound(m_explosion_sound);
}