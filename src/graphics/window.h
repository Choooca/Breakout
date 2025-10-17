#pragma once
#include <SDL3/SDL.h>

class Window {
public:
	Window(int window_width = 900, int window_height = 900);
	~Window();

	void RenderBegin();
	void RenderEnd();

	SDL_Window* GetWindow() const { return m_window; }
	SDL_Renderer* GetRenderer() const { return m_renderer; }

	float GetWidth() const { return m_window_width; }
	float GetHeight() const { return m_window_height; }

private:
	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer;

	int m_window_width;
	int m_window_height;
};