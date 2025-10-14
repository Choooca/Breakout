#include "ball.h"
#include <algorithm>
#include <iostream>
#include <cmath>
#include <utility/aabb_utility.h>
#include <utility/math_utils.h>

Ball::Ball(float position_x, float position_y, float width, float height, Color color, std::string name, float speed)
	: MovingEntity(position_x, position_y, width, height, color, name, speed),
	  m_dir_x(-1),
	  m_dir_y(-1)
	  { }

void Ball::Update(const Game& game) {

	if (m_position_x <= m_width * .5f)
	{
		m_position_x = m_width * .5f;
		ReflectVector(m_dir_x, m_dir_y, 1.0f, 0.0f);
	}

	if (m_position_x >= game.m_window->GetWidth() - m_width * .5f) {
		m_position_x = game.m_window->GetWidth() - m_width * .5f;
		ReflectVector(m_dir_x, m_dir_y, -1.0f, 0.0f);
	}
	
	if (m_position_y <= m_height * .5f)
	{
		m_position_y = m_height * .5f;
		ReflectVector(m_dir_x, m_dir_y, 0.0f, 1.0f);
	}

	if (m_position_y >= game.m_window->GetHeight() - m_height * .5f)
	{
		//Perdu
		m_position_y = game.m_window->GetHeight() - m_height * .5f;
		ReflectVector(m_dir_x, m_dir_y, 0.0f, -1.0f);
	}

	float length = std::sqrt(m_dir_x * m_dir_x + m_dir_y * m_dir_y);
	m_dir_x /= length;
	m_dir_y /= length;

	m_velocity_x = m_velocity_y = 0;

	m_velocity_x = game.m_input_handler->GetDeltaTime() * m_speed * m_dir_x;
	m_velocity_y = game.m_input_handler->GetDeltaTime() * m_speed * m_dir_y;
}

void Ball::OnHit(Hit hit_result, std::weak_ptr<Entity> other_entity) {

	std::shared_ptr<Entity> entity = other_entity.lock();
	if (!entity) return;

	entity->ModifyBallDirection(m_dir_x, m_dir_y, hit_result);
}

