#include "ball.h"
#include <algorithm>

Ball::Ball(float position_x, float position_y, float width, float height, Color color)
	: Entity(position_x, position_y, width, height, color),
	  m_speed(300),
	  m_dir_x(1),
	  m_dir_y(-1){ }

void Ball::Update(const Game& game) {
	m_position_x += game.m_input_handler->GetDeltaTime() * m_speed * m_dir_x;
	m_position_y += game.m_input_handler->GetDeltaTime() * m_speed * m_dir_y;

	if (m_position_x <= m_width * .5f)
	{
		m_position_x = m_width * .5f;
		m_dir_x = -1;
	}

	if (m_position_x >= game.m_window->GetWidth() - m_width * .5f) {
		m_position_x = game.m_window->GetWidth() - m_width * .5f;
		m_dir_x = 1;
	}
	
	if (m_position_y <= m_height * .5f)
	{
		m_position_y = m_height * .5f;
		m_dir_y *= -1;
	}

	if (m_position_y >= game.m_window->GetHeight() - m_height * .5f)
	{
		//Perdu
		m_position_y = game.m_window->GetHeight() - m_height * .5f;
		m_dir_y = 1;
	}
}

