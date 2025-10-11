#include "input_handler.h"
#include <SDL3/SDL.h>

InputHandler::InputHandler(SDL_Window* window) :
	m_current_time(0), m_last_time(0), m_delta_time(0), m_quit(false)
{
	SDL_SetWindowRelativeMouseMode(window, true);
}

InputHandler::~InputHandler() {}

void InputHandler::CalculateDeltaTime() {
	m_current_time = SDL_GetTicks();
	m_delta_time = (m_last_time - m_current_time) / 1000.0f;
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