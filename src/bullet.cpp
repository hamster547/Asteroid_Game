#include "bullet.hpp"
#include "config.hpp"

void Bullet::Activate(const Vector2 ShipPos, const float ShipVelX) {
	pos = ShipPos;
	initVel.x = ShipVelX;
	initVel.y = speed;
	isActive = true;
}

bool Bullet::OnScreen() {
	if (pos.y + height <= 0.0f) return false;
	if (pos.x + width <= 0.0f) return false;
	if (pos.x >= config::SCREEN_WIDTH) return false;
	return true;
}

void Bullet::Update(float dt) {
	pos.x += initVel.x * dt;
	pos.y -= initVel.y * dt;
	isActive = OnScreen();
}

void Bullet::Draw() {
	DrawRectangle(pos.x, pos.y, width, height, YELLOW);
}