#pragma once
#include <raylib.h>

class Ship {
	public:
	Vector2 pos;
	Vector2 velocity = {0, 0};
	const Vector2 size = {50, 50};
	float shootCooldown = 0.0f;
	const float acceleration = 1800.0f;
	const float maxSpeed = 10800.0f;
	const float friction = 0.95f;

	Ship();

	void Update(float dt);

	void Draw();
};