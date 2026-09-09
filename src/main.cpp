#include <raylib.h>
#include <raymath.h>

class Ship {
	public:
	Vector2 pos;
	Vector2 velocity = {0, 0};
	const Vector2 size = {50, 50};
	const float acceleration = 0.5f; // make it a bit fun to steer
	const float maxSpeed = 3.0f;
	const float friction = 0.95f;
	const int screenWidth;
	const int screenHeight;

	Ship(const Vector2 screenSize) : screenWidth(static_cast<int>(screenSize.x)), screenHeight(static_cast<int>(screenSize.y)) {
		pos = { (screenWidth - size.x) / 2.0f, (screenHeight - size.y) / 2.0f };
	}

	void Update(float dt) {
		// screen warp on x
		// not equal or youll constantly jump on the edge
		if (pos.x + size.x < 0.0f) pos.x = screenWidth - size.x;
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

	Game(const Vector2 screenSize) : ship(screenSize) {

	}

	void Update() {
		ship.Update(GetFrameTime());
	}

	void Draw() {
		ship.Draw();
	}
};

int main() {
	const int screenWidth = 800;
	const int screenHeight = 800;

	InitWindow(screenWidth, screenHeight, "asteroid game");
	SetTargetFPS(60);

	Game game({screenWidth, screenHeight});

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