#include "paddle.h"
#include <iostream>
#include <algorithm>

Paddle::Paddle(float position_x, float position_y, float width, float height, Color color)
	: Entity(position_x, position_y, width, height, color),
	  m_speed(500) { }


void Paddle::Update(const Game& game) {
	Input(game.m_input_handler, game.m_window);
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
