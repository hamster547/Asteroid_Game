#pragma once

class Window {
	public:
	Window(int sw, int sh, const char * title, int fps);
	
	~Window();

	bool ShouldClose();

	void StartFrame();

	void EndFrame();
};