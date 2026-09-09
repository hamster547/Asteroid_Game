#pragma once
#include "ship.hpp"
#include "bullet.hpp"
#include "asteroid.hpp"
#include "config.hpp"

class Game {
	public:
	Ship ship;
	Bullet bullets[config::MAX_BULLET_AMOUNT];
	Asteroid asteroids[config::MAX_ASTEROID_AMOUNT];
	float asteroidSpawnTimer = 0.0f;
	bool gameOver = false;

	int GetNextFreeBullet();

	int GetNextFreeAstroid();

	void CheckAsteroidCollision(Asteroid& asteroid);

	void Update();

	void Draw();
};