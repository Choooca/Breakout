#include "ball.h"

Ball::Ball(int screen_width, int screen_height)
	: Entity(screen_width * .5f, screen_height * 0.7f, 20, 20),
	  m_speed(300) { }

void Ball::Update(const Game& game) {
	Render(game.m_window);
}

void Ball::Render(const std::unique_ptr<Window>& window) {

	SDL_SetRenderDrawColor(window->GetRenderer(), 255, 0, 0, 255);

	SDL_FRect paddle_rect = { m_position_x - m_width * .5f, m_position_y - m_height * .5f, m_width, m_height };
	SDL_RenderFillRect(window->GetRenderer(), &paddle_rect);
}