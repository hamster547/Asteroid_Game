#include "game.hpp"


int Game::GetNextFreeBullet() {
	for (int i = 0; i < config::MAX_BULLET_AMOUNT; i++) {
		if (!bullets[i].isActive) return i;
	}
	// fallback: return the first bullet
	return 0;
}

int Game::GetNextFreeAstroid() {
	for (int i = 0; i < config::MAX_ASTEROID_AMOUNT; i++) {
		if (!asteroids[i].isActive) return i;
	}
	// fallback: return the first bullet
	return 0;
}

void Game::CheckAsteroidCollision(Asteroid& asteroid) {
	for (auto& bullet : bullets) {
		if (bullet.isActive) {
			Rectangle bulletHitbox = {
				bullet.pos.x,
				bullet.pos.y,
				bullet.width,
				bullet.height
			};
			if (CheckCollisionCircleRec(asteroid.pos, asteroid.radius, bulletHitbox)) {
				bullet.isActive = false;
				asteroid.isActive = false;
				return;
			}
		}
	}
	Rectangle shipHitbox = {
		ship.pos.x,
		ship.pos.y,
		ship.size.x,
		ship.size.y,
	};
	if (CheckCollisionCircleRec(asteroid.pos, asteroid.radius, shipHitbox)) {
		gameOver = true;
	}
}

void Game::Update() {
	if (!gameOver) {
		float dt = GetFrameTime();
		ship.Update(dt);
	
		for (auto& bullet : bullets) {
			if (bullet.isActive) {
				bullet.Update(dt);
			}
		}
		for (auto& asteroid : asteroids) {
			if (asteroid.isActive) {
				asteroid.Update(dt);
				CheckAsteroidCollision(asteroid);
			}
		}

		asteroidSpawnTimer -= dt;

		if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			if (ship.shootCooldown <= 0.0f) {
				bullets[GetNextFreeBullet()].Activate({ship.pos.x + ship.size.x / 2.0f, ship.pos.y - 10}, ship.velocity.x);
				ship.shootCooldown = 0.35f;
			}
		}
		if (asteroidSpawnTimer <= 0.0f) {
			for (int i = 0; i < 10; i++) {
				asteroids[GetNextFreeAstroid()].Activate();
			}
			asteroidSpawnTimer = 1.5f;
		}
	}
}

void Game::Draw() {
	if (!gameOver) {
		ship.Draw();
		for (auto& bullet : bullets) {
			if (bullet.isActive) {
				bullet.Draw();
			}
		}
		for (auto& asteroid : asteroids) {
			if (asteroid.isActive) {
				asteroid.Draw();
			}
		}
	}
	else {
		// non centered but who cares...
		DrawText("GAME OVER T^T", 50, 300, 75, WHITE);
	}
}