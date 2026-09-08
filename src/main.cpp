#include <raylib.h>

int main() {
	const int screenWidth = 800;
	const int screenHeight = 800;

	InitWindow(screenWidth, screenHeight, "asteroid game");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		
		
		BeginDrawing();

		ClearBackground(BLACK);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}