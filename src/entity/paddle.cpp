#include "paddle.h"
#include <iostream>
#include <algorithm>

Paddle::Paddle(float position_x, float position_y, float width, float height, Color color, std::string name, float speed)
	: MovingEntity(position_x, position_y, width, height, color, name, speed){}


void Paddle::Update(const Game& game) {
	Input(game.m_input_handler, game.m_window);
}

void Paddle::Input(const std::unique_ptr<InputHandler>& input_handler, const std::unique_ptr<Window>& window) {
	m_velocity_x = m_velocity_y = 0;
	
	if (input_handler->GetKey(SDLK_Q)) {
		m_velocity_x = m_speed * input_handler->GetDeltaTime();
	}

	if (input_handler->GetKey(SDLK_D)) {
		m_velocity_x = -m_speed * input_handler->GetDeltaTime();
	}

	if (m_position_x + m_velocity_x < m_width * .5f) m_velocity_x = m_width * .5f - m_position_x;
	if (m_position_x + m_velocity_y > window->GetWidth() - m_width * .5f) m_velocity_x = window->GetWidth() - m_width * .5f - m_position_x;

}
