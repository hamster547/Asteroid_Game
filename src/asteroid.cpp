#include "asteroid.hpp"
#include "config.hpp"

void Asteroid::Activate() {
	radius = GetRandomValue(500, 1000) / 10.0f;
	pos.x = GetRandomValue(radius, config::SCREEN_WIDTH - radius);
	pos.y = -radius;

	speed = GetRandomValue(9000, 12000) / 100.0f;
	// randomize color
	int colorVariant = GetRandomValue(-25, 25);
	color = GRAY;
	color.r += colorVariant;
	color.g += colorVariant;
	color.b += colorVariant;

	isActive = true;
}

bool Asteroid::OnScreen() {
	return !(pos.y - radius >= config::SCREEN_HEIGHT);
}

void Asteroid::Update(float dt) {
	pos.y += speed * dt;
	isActive = OnScreen();
}

void Asteroid::Draw() {
	DrawCircle(pos.x, pos.y, radius, color);
}