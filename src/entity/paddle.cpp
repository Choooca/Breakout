#include "paddle.h"
#include <iostream>
#include <algorithm>

Paddle::Paddle(float position_x, float position_y, float width, float height, Color color, std::string name, float speed)
	: MovingEntity(position_x, position_y, width, height, color, name, speed),
	  m_max_influence(.5f){}


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

void Paddle::ModifyBallDirection(float &dir_x, float &dir_y, const Hit& hit_result) {
	float ratio = std::clamp((m_position_x - hit_result.collision_point.m_x) / m_width,-.5f,.5f) * 2.0f;
	

	if (std::abs(hit_result.normal.m_y) > 0.0f) {
		dir_y = 1.0f;
		dir_x += ratio * m_max_influence;
	}
}