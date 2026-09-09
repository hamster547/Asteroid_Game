#pragma once
#include <raylib.h>

// if we have 10k bullets i know itll be better to seperate pos, vel and isActive in seperate lists to make the cpu cache like me
class Bullet {
	public:
	Vector2 pos;
	Vector2 initVel; // y is just speed, but x can be effected by the ship's velocity
	bool isActive = false;
	// im not an expert but this should make it so every bullet doesnt spawn its own variables
	static constexpr float speed = 600.0f;
	static constexpr float width = 5.0f;
	static constexpr float height = 10.0f;

	void Activate(const Vector2 ShipPos, const float ShipVelX);

	bool OnScreen();

	void Update(float dt);

	void Draw();
};