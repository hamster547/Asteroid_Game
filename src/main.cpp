#include <raylib.h>
#include <raymath.h>
#include "config.hpp"
#include "window.hpp"
#include "game.hpp"

int main() {
	// also initiate a raylib window
	Window window(config::SCREEN_WIDTH, config::SCREEN_HEIGHT, "Asteroids Game", 60);

	Game game;

	while (!window.ShouldClose()) {
		
		game.Update();
		
		window.StartFrame();
		game.Draw();
		window.EndFrame();
	}
	
	// window deconstructor will close the raylib window

	return 0;
}