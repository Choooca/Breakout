#include "ball.h"
#include <algorithm>
#include <iostream>
#include <utility/aabb_utility.h>

Ball::Ball(float position_x, float position_y, float width, float height, Color color, std::string name, float speed)
	: MovingEntity(position_x, position_y, width, height, color, name, speed),
	  m_dir_x(1),
	  m_dir_y(-1)
	  { }

void Ball::Update(const Game& game) {

	m_velocity_x = m_velocity_y = 0;

	m_velocity_x = game.m_input_handler->GetDeltaTime() * m_speed * m_dir_x;
	m_velocity_y = game.m_input_handler->GetDeltaTime() * m_speed * m_dir_y;

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
		m_dir_y = -1;
	}

	if (m_position_y >= game.m_window->GetHeight() - m_height * .5f)
	{
		//Perdu
		m_position_y = game.m_window->GetHeight() - m_height * .5f;
		m_dir_y = 1;
	}
}

void Ball::OnHit(Hit hit_result, std::weak_ptr<Entity> other_entity) {

	if (hit_result.normal.m_y == 0.0f) {
		m_dir_x = hit_result.normal.m_x > 0.0f ? -1 : 1;
	} else {
		m_dir_y = hit_result.normal.m_y > 0.0f ? -1 : 1;
	}

	//std::cout << (hit_result.collision_point.m_x - other_entity.lock()->GetXPos()) / other_entity.lock()->GetWidth() << std::endl;
}
