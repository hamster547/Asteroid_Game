#include "window.hpp"
#include <raylib.h>

Window::Window(int sw, int sh, const char * title, int fps) {
	InitWindow(sw, sh, title);
	SetTargetFPS(fps);
}

Window::~Window() {
	CloseWindow();
}

bool Window::ShouldClose() {
	return WindowShouldClose();
}

void Window::StartFrame() {
	BeginDrawing();
	ClearBackground(BLACK);
}

void Window::EndFrame() {
	EndDrawing();
}