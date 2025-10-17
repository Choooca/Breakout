#include "paddle.h"
#include <core/input_handler.h>
#include <core/game.h>
#include <entity/entity.h>
#include <iostream>
#include <algorithm>
#include <graphics/window.h>
#include <state/play_state.h>
#include <vector>

Paddle::Paddle(Vector2 position, Vector2 size, SDL_Color color, std::string name, float speed, SDL_Texture* texture)
	: MovingEntity(position, size, color, name, speed, texture),
	  m_max_influence(1.1f), m_move_scale_factor(.2f){

	m_flag = EntityFlags::FLAG_PADDLE;
	m_collide_mask = EntityFlags::FLAG_BRICK | EntityFlags::FLAG_BALL | EntityFlags::FLAG_POWERUP;

}


void Paddle::Update(const std::unique_ptr<InputHandler>& input_handler, int window_height) {
	Entity::Update(input_handler, window_height);
	Input(input_handler);
}

void Paddle::OnHit(Hit hit_result, std::shared_ptr<Entity> other_entity) {
	MovingEntity::OnHit(hit_result, other_entity);

	if ((other_entity->GetFlag() & FLAG_BALL) ) {

		m_colliding_balls[other_entity] = other_entity->GetPosition().x - m_position.x;;
	}
	
}

void Paddle::HitAnim(float duration) {

	m_coroutines->Start([this, m_elapsed = 0.0f, duration](float delta_time) mutable {
		m_elapsed += delta_time;

		if (m_elapsed >= duration) {
			m_render_offset.y = 0;
			return true;
		}

		m_render_offset.y = std::sin(3.1415 * (m_elapsed / duration)) * 20.0f;
		return false;
		});
}

void Paddle::Input(const std::unique_ptr<InputHandler>& input_handler) {
	m_velocity.x = 0;

	if (input_handler->GetKey(SDLK_Q)) {
		m_velocity.x = -m_speed * input_handler->GetDeltaTime();
	}

	if (input_handler->GetKey(SDLK_D)) {
		m_velocity.x = m_speed * input_handler->GetDeltaTime();
	} 


	std::erase_if(m_colliding_balls, [&](auto& kv) {
		std::shared_ptr<Entity> ball = kv.first.lock();
		if (!ball) return true;

		if (input_handler->GetKey(SDLK_SPACE)) {
			ball->SetUpdateEnable(false);
			ball->SetPosition(
				{ m_position.x + kv.second,
				m_position.y - m_size.y * .5f - ball->GetSize().y * .5f }
			);
			return false;
		}
		else {
			ball->SetUpdateEnable(true);
			HitAnim(.2f);
			return true;
		}
		});
}

void Paddle::Render(const std::unique_ptr<Window>& window) {
	
	Vector2 base_size = m_size;
	
	if (m_velocity.x != 0)
	{
		m_size.x = base_size.x * (1 + m_move_scale_factor);
		m_size.y = base_size.y * (1 + m_move_scale_factor);
	}

	Entity::Render(window);

	m_size = base_size;
}

void Paddle::ModifyBallDirection(float &dir_x, float &dir_y, const Hit& hit_result) {
	float ratio = std::clamp((m_position.x - hit_result.collision_point.x) / m_size.x,-.5f,.5f) * 2.0f;
	
	dir_y = -1.0f;
	dir_x = -ratio * m_max_influence;
}