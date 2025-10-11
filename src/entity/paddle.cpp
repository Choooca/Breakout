#include "paddle.h"
#include <iostream>
#include <algorithm>

Paddle::Paddle(int screen_width, int screen_height)
	: Entity(screen_width * .5f, screen_height * 0.9f, 100, 20),
	  m_speed(300) { }


void Paddle::Update(const Game& game) {
	Input(game.m_input_handler, game.m_window);
	Render(game.m_window);
}

void Paddle::Input(const std::unique_ptr<InputHandler>& input_handler, const std::unique_ptr<Window>& window) {
	if (input_handler->GetKey(SDLK_Q)) {
		m_position_x += m_speed * input_handler->GetDeltaTime();
	}

	if (input_handler->GetKey(SDLK_D)) {
		m_position_x -= m_speed * input_handler->GetDeltaTime();
	}

	m_position_x = std::clamp(m_position_x, 0.0f + m_width * .5f, window->GetWidth() - m_width * .5f);

}

void Paddle::Render(const std::unique_ptr<Window>& window) {
	SDL_SetRenderDrawColor(window->GetRenderer(), 0, 255, 0, 255);

	SDL_FRect paddle_rect = { m_position_x - m_width * .5f, m_position_y - m_height * .5f, m_width, m_height};
	SDL_RenderFillRect(window->GetRenderer(), &paddle_rect);
}