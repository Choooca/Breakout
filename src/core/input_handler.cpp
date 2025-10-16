#include "input_handler.h"
#include <SDL3/SDL.h>
#include <iostream>

InputHandler::InputHandler(SDL_Window* window) :
	m_delta_time(0), m_quit(false)
{
	SDL_SetWindowRelativeMouseMode(window, true);

	m_last_time = m_current_time = SDL_GetPerformanceCounter();
}

InputHandler::~InputHandler() {}

void InputHandler::CalculateDeltaTime() {
	m_current_time = SDL_GetPerformanceCounter();

	uint64_t delta_tick = m_current_time - m_last_time;
	uint64_t frequency = SDL_GetPerformanceFrequency();

	m_delta_time = static_cast<float>(delta_tick) / static_cast<float>(frequency);

	m_last_time = m_current_time;
}

void InputHandler::Update() {
	CalculateDeltaTime();

	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
			m_quit = true;
			break;
		case SDL_EVENT_KEY_DOWN:
			if (event.key.key < 128) m_keys[event.key.key] = true;
			break;
		case SDL_EVENT_KEY_UP:
			if (event.key.key < 128) m_keys[event.key.key] = false;
			break;
		default:
			break;
		}
	}
}

bool InputHandler::GetKey(int key_code) const {
	return m_keys[key_code];
}