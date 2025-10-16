#include "window.h"
#include <cstdio>

Window::Window(int window_width, int window_height) 
: m_window_width(window_width), m_window_height(window_height)
{
	SDL_Init(SDL_INIT_VIDEO);

	m_window = SDL_CreateWindow("Breakout", window_width, window_height, SDL_WINDOW_OPENGL);

	m_renderer = SDL_CreateRenderer(m_window, NULL);
}

Window::~Window() {
	if(m_window) SDL_DestroyWindow(m_window);
	if (m_renderer) SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}

void Window::RenderBegin() {
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 30, 255);
	SDL_RenderClear(m_renderer);
}

void Window::RenderEnd() {
	SDL_RenderPresent(m_renderer);
}