#include <raylib.h>
#include <raymath.h>
#include "config.hpp"
#include "game.hpp"

// class Asteroid {
// 	public:
// 	Vector2 pos = {0, 0};
// 	float speed = 0;
// 	float radius = 0;
// 	bool isActive = false;
// 	Color color = GRAY;

// 	void Activate() {
// 		radius = GetRandomValue(500, 1000) / 10.0f;
// 		pos.x = GetRandomValue(radius, config::SCREEN_WIDTH - radius);
// 		pos.y = -radius;

// 		speed = GetRandomValue(9000, 12000) / 100.0f;
// 		// randomize color
// 		int colorVariant = GetRandomValue(-25, 25);
// 		color = GRAY;
// 		color.r += colorVariant;
// 		color.g += colorVariant;
// 		color.b += colorVariant;

// 		isActive = true;
// 	}

// 	bool OnScreen() {
// 		return !(pos.y - radius >= config::SCREEN_HEIGHT);
// 	}

// 	void Update(float dt) {
// 		pos.y += speed * dt;
// 		isActive = OnScreen();
// 	}

// 	void Draw() {
// 		DrawCircle(pos.x, pos.y, radius, color);
// 	}
// };

// // if we have 10k bullets i know itll be better to seperate pos, vel and isActive in seperate lists to make the cpu cache like me
// class Bullet {
// 	public:
// 	Vector2 pos;
// 	Vector2 initVel; // y is just speed, but x can be effected by the ship's velocity
// 	bool isActive = false;
// 	// im not an expert but this should make it so every bullet doesnt spawn its own variables
// 	static constexpr float speed = 600.0f;
// 	static constexpr float width = 5.0f;
// 	static constexpr float height = 10.0f;

// 	void Activate(const Vector2 ShipPos, const float ShipVelX) {
// 		pos = ShipPos;
// 		initVel.x = ShipVelX;
// 		initVel.y = speed;
// 		isActive = true;
// 	}

// 	bool OnScreen() {
// 		if (pos.y + height <= 0.0f) return false;
// 		if (pos.x + width <= 0.0f) return false;
// 		if (pos.x >= config::SCREEN_WIDTH) return false;
// 		return true;
// 	}

// 	void Update(float dt) {
// 		pos.x += initVel.x * dt;
// 		pos.y -= initVel.y * dt;
// 		isActive = OnScreen();
// 	}

// 	void Draw() {
// 		DrawRectangle(pos.x, pos.y, width, height, YELLOW);
// 	}
// };

// class Ship {
// 	public:
// 	Vector2 pos;
// 	Vector2 velocity = {0, 0};
// 	const Vector2 size = {50, 50};
// 	float shootCooldown = 0.0f;
// 	const float acceleration = 1800.0f;
// 	const float maxSpeed = 10800.0f;
// 	const float friction = 0.95f;

// 	Ship() {
// 		pos = { (config::SCREEN_WIDTH - size.x) / 2.0f, (config::SCREEN_HEIGHT - size.y) / 2.0f };
// 	}

// 	void Update(float dt) {
// 		// screen warp on x
// 		// not equal or youll constantly jump on the edge
// 		if (pos.x + (size.x / 2.0f) < 0.0f) pos.x = config::SCREEN_WIDTH - (size.x / 2.0f);
// 		if (pos.x + (size.x / 2.0f) > config::SCREEN_WIDTH) pos.x = -size.x / 2.0f;

// 		// block exiting the screen on y and bounce off
// 		if (pos.y + size.y >= config::SCREEN_HEIGHT) {
// 			pos.y = config::SCREEN_HEIGHT - size.y;
// 			velocity.y *= -1.0f;
// 		}
// 		if (pos.y <= 0.0f) {
// 			pos.y = 0.0f;
// 			velocity.y *= -1.0f;
// 		}
		
// 		// multi by dt in here makes it feel more 'dragging'
// 		if (IsKeyDown(KEY_W)) {
// 			velocity.y -= acceleration * dt;
// 		}
// 		if (IsKeyDown(KEY_S)) {
// 			velocity.y += acceleration * dt;
// 		}
// 		if (IsKeyDown(KEY_A)) {
// 			velocity.x -= acceleration * dt;
// 		}
// 		if (IsKeyDown(KEY_D)) {
// 			velocity.x += acceleration * dt;
// 		}

// 		velocity.x = Clamp(velocity.x, -maxSpeed, maxSpeed);
// 		velocity.y = Clamp(velocity.y, -maxSpeed, maxSpeed);

// 		pos.x += velocity.x * dt;// * 60.0f; // just to speed up after dt
// 		pos.y += velocity.y * dt;// * 60.0f;


// 		float dtFriction = std::pow(friction, 60.0f*dt);
// 		velocity.x *= dtFriction;
// 		velocity.y *= dtFriction;

// 		if (shootCooldown > 0.0f) shootCooldown -= dt;
// 	}

// 	void Draw() {
// 		DrawRectangle(pos.x, pos.y, size.x, size.y, RED);
// 		// the most simple way for a fun screen warp effect
// 		// its only two rectangles so it doesnt really effect preformance
// 		DrawRectangle(pos.x + config::SCREEN_WIDTH, pos.y, size.x, size.y, RED);
// 		DrawRectangle(pos.x - config::SCREEN_WIDTH, pos.y, size.x, size.y, RED);
// 	}
// };

// class Game {
// 	public:
// 	Ship ship;
// 	Bullet bullets[config::MAX_BULLET_AMOUNT];
// 	Asteroid asteroids[config::MAX_ASTEROID_AMOUNT];
// 	float asteroidSpawnTimer = 0.0f;
// 	bool gameOver = false;

// 	int GetNextFreeBullet() {
// 		for (int i = 0; i < config::MAX_BULLET_AMOUNT; i++) {
// 			if (!bullets[i].isActive) return i;
// 		}
// 		// fallback: return the first bullet
// 		return 0;
// 	}

// 	int GetNextFreeAstroid() {
// 		for (int i = 0; i < config::MAX_ASTEROID_AMOUNT; i++) {
// 			if (!asteroids[i].isActive) return i;
// 		}
// 		// fallback: return the first bullet
// 		return 0;
// 	}

// 	void CheckAsteroidCollision(Asteroid& asteroid) {
// 		for (auto& bullet : bullets) {
// 			if (bullet.isActive) {
// 				Rectangle bulletHitbox = {
// 					bullet.pos.x,
// 					bullet.pos.y,
// 					bullet.width,
// 					bullet.height
// 				};
// 				if (CheckCollisionCircleRec(asteroid.pos, asteroid.radius, bulletHitbox)) {
// 					bullet.isActive = false;
// 					asteroid.isActive = false;
// 					return;
// 				}
// 			}
// 		}
// 		Rectangle shipHitbox = {
// 			ship.pos.x,
// 			ship.pos.y,
// 			ship.size.x,
// 			ship.size.y,
// 		};
// 		if (CheckCollisionCircleRec(asteroid.pos, asteroid.radius, shipHitbox)) {
// 			gameOver = true;
// 		}
// 	}

// 	void Update() {
// 		if (!gameOver) {
// 			float dt = GetFrameTime();
// 			ship.Update(dt);
		
// 			for (auto& bullet : bullets) {
// 				if (bullet.isActive) {
// 					bullet.Update(dt);
// 				}
// 			}
// 			for (auto& asteroid : asteroids) {
// 				if (asteroid.isActive) {
// 					asteroid.Update(dt);
// 					CheckAsteroidCollision(asteroid);
// 				}
// 			}

// 			asteroidSpawnTimer -= dt;

// 			if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
// 				if (ship.shootCooldown <= 0.0f) {
// 					bullets[GetNextFreeBullet()].Activate({ship.pos.x + ship.size.x / 2.0f, ship.pos.y - 10}, ship.velocity.x);
// 					ship.shootCooldown = 0.35f;
// 				}
// 			}
// 			if (asteroidSpawnTimer <= 0.0f) {
// 				for (int i = 0; i < 10; i++) {
// 					asteroids[GetNextFreeAstroid()].Activate();
// 				}
// 				asteroidSpawnTimer = 1.5f;
// 			}
// 		}
// 	}

// 	void Draw() {
// 		if (!gameOver) {
// 			ship.Draw();
// 			for (auto& bullet : bullets) {
// 				if (bullet.isActive) {
// 					bullet.Draw();
// 				}
// 			}
// 			for (auto& asteroid : asteroids) {
// 				if (asteroid.isActive) {
// 					asteroid.Draw();
// 				}
// 			}
// 		}
// 		else {
// 			// non centered but who cares...
// 			DrawText("GAME OVER T^T", 50, 300, 75, WHITE);
// 		}
// 	}
// };

int main() {
	InitWindow(config::SCREEN_WIDTH, config::SCREEN_HEIGHT, "asteroid game");
	SetTargetFPS(config::targetFPS);

	Game game;

	while (!WindowShouldClose()) {
		
		game.Update();
		
		BeginDrawing();

		ClearBackground(BLACK);
		game.Draw();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}