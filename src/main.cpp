#include <raylib.h>
#include <raymath.h>

const int screenWidth = 800;
const int screenHeight = 800;

// if we have 10k bullets i know itll be better to seperate pos, vel and isActive in seperate lists to make the cpu cache like me
class Bullet {
	public:
	Vector2 pos;
	Vector2 initVel; // y is just speed, but x can be effected by the ship's velocity
	bool isActive = false;
	// im not an expert but this should make it so every bullet doesnt spawn its own variables
	static constexpr float speed = 10.0f;
	static constexpr float width = 5.0f;
	static constexpr float height = 10.0f;

	void ActivateBullet(const Vector2 ShipPos, const float ShipVelX) {
		pos = ShipPos;
		initVel.x = speed * ShipVelX * 3.0f;
		initVel.y = speed;
		isActive = true;
	}

	bool OnScreen() {
		if (pos.y + height <= 0.0f) return false;
		if (pos.x + width <= 0.0f) return false;
		if (pos.x >= screenWidth) return false;
		return true;
	}

	void Update() {
		pos.x += initVel.x;
		pos.y -= initVel.y;
		isActive = OnScreen();
	}

	void Draw() {
		DrawRectangle(pos.x, pos.y, width, height, YELLOW);
	}
};

class Ship {
	public:
	Vector2 pos;
	Vector2 velocity = {0, 0};
	const Vector2 size = {50, 50};
	float shootCooldown = 0.0f;
	const float acceleration = 0.5f; // make it a bit fun to steer
	const float maxSpeed = 3.0f;
	const float friction = 0.95f;

	Ship() {
		pos = { (screenWidth - size.x) / 2.0f, (screenHeight - size.y) / 2.0f };
	}

	void Update(float dt) {
		// screen warp on x
		// not equal or youll constantly jump on the edge
		if (pos.x< 0.0f) pos.x = screenWidth;
		if (pos.x > screenWidth) pos.x = 0.0f;

		// block exiting the screen on y and bounce off
		if (pos.y + size.y >= screenHeight) {
			pos.y = screenHeight - size.y;
			velocity.y *= -1.0f;
		}
		if (pos.y <= 0.0f) {
			pos.y = 0.0f;
			velocity.y *= -1.0f;
		}
		
		// multi by dt in here makes it feel more 'dragging'
		if (IsKeyDown(KEY_W)) {
			velocity.y -= acceleration * dt;
		}
		if (IsKeyDown(KEY_S)) {
			velocity.y += acceleration * dt;
		}
		if (IsKeyDown(KEY_A)) {
			velocity.x -= acceleration * dt;
		}
		if (IsKeyDown(KEY_D)) {
			velocity.x += acceleration * dt;
		}

		velocity.x = Clamp(velocity.x, -maxSpeed, maxSpeed);
		velocity.y = Clamp(velocity.y, -maxSpeed, maxSpeed);

		pos.x += velocity.x * 60.0f; // just to speed up after dt
		pos.y += velocity.y * 60.0f;

		velocity.x *= friction;
		velocity.y *= friction;

		if (shootCooldown > 0.0f) shootCooldown -= dt;
	}

	void Draw() {
		DrawRectangle(pos.x, pos.y, size.x, size.y, RED);
		// the most simple way for a fun screen warp effect
		// its only two rectangles so it doesnt really effect preformance
		DrawRectangle(pos.x + screenWidth, pos.y, size.x, size.y, RED);
		DrawRectangle(pos.x - screenWidth, pos.y, size.x, size.y, RED);
	}
};

class Game {
	public:
	Ship ship;
	Bullet bullets[50];

	int GetFreeBullet() {
		for (int i = 0; i < 100; i++) {
			if (!bullets[i].isActive) return i;
		}
		// fallback: return the first bullet
		return 0;
	}

	void Update() {
		float dt = GetFrameTime();
		ship.Update(dt);
		
		for (auto& bullet : bullets) {
			if (bullet.isActive) {
				bullet.Update();
			}
		}

		if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			if (ship.shootCooldown <= 0.0f) {
				bullets[GetFreeBullet()].ActivateBullet({ship.pos.x + ship.size.x / 2.0f, ship.pos.y - 10}, ship.velocity.x);
				ship.shootCooldown = 0.15f;
			}
		}
	}

	void Draw() {
		ship.Draw();
		for (auto& bullet : bullets) {
			if (bullet.isActive) {
				bullet.Draw();
			}
		}
	}
};

int main() {
	InitWindow(screenWidth, screenHeight, "asteroid game");
	SetTargetFPS(60);

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