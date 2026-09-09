#include "ship.hpp"
#include "config.hpp"
#include <raymath.h>

Ship::Ship() {
	pos = { (config::SCREEN_WIDTH - size.x) / 2.0f, (config::SCREEN_HEIGHT - size.y) / 2.0f };
}

void Ship::Update(float dt) {
	// screen warp on x
	// not equal or youll constantly jump on the edge
	if (pos.x + (size.x / 2.0f) < 0.0f) pos.x = config::SCREEN_WIDTH - (size.x / 2.0f);
	if (pos.x + (size.x / 2.0f) > config::SCREEN_WIDTH) pos.x = -size.x / 2.0f;

	// block exiting the screen on y and bounce off
	if (pos.y + size.y >= config::SCREEN_HEIGHT) {
		pos.y = config::SCREEN_HEIGHT - size.y;
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

	pos.x += velocity.x * dt;// * 60.0f; // just to speed up after dt
	pos.y += velocity.y * dt;// * 60.0f;


	float dtFriction = std::pow(friction, 60.0f*dt);
	velocity.x *= dtFriction;
	velocity.y *= dtFriction;

	if (shootCooldown > 0.0f) shootCooldown -= dt;
}

void Ship::Draw() {
	DrawRectangle(pos.x, pos.y, size.x, size.y, RED);
	// the most simple way for a fun screen warp effect
	// its only two rectangles so it doesnt really effect preformance
	DrawRectangle(pos.x + config::SCREEN_WIDTH, pos.y, size.x, size.y, RED);
	DrawRectangle(pos.x - config::SCREEN_WIDTH, pos.y, size.x, size.y, RED);
}