#pragma once
#include <raylib.h>

class Asteroid {
	public:
	Vector2 pos = {0, 0};
	float speed = 0;
	float radius = 0;
	bool isActive = false;
	Color color = GRAY;

	void Activate();

	bool OnScreen();

	void Update(float dt);

	void Draw();
};