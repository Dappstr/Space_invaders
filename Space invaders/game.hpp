#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mystery_ship.hpp"

class Game {
public:
	Game();
	void draw();
	void update();
	void handle_input();
	void delete_inactive_lasers();
	std::vector<Obstacle> create_obstacles();
	std::vector<Alien> create_aliens();
	void move_aliens();
	void move_down_aliens(const int distance);
	void alien_shoot_laser();
	void check_for_collisions();
	void game_over();
	bool m_run;
	void reset();
	void init_game();
	void check_for_high_score();
	void save_high_score_to_file(const int high_score);
	size_t load_high_score_from_file();
	Music m_music;
	~Game();

	size_t m_lives;
	size_t m_score;
	size_t m_high_score;

private:
	Space_ship m_space_ship;
	std::vector<Obstacle> m_obstacles;
	std::vector<Alien> m_aliens;
	int m_aliens_direction;
	std::vector<Laser> m_alien_lasers;
	constexpr static float m_alien_laser_shoot_interval{0.35};
	float m_time_last_alien_fired;
	Mystery_ship m_mystery_ship;
	float m_mystery_ship_spawn_interval;
	float m_time_last_spawn;
	Sound m_explosion_sound;
};