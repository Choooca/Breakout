#include "paddle.h"
#include <core/input_handler.h>
#include <core/game.h>
#include <entity/entity.h>
#include <iostream>
#include <algorithm>
#include <graphics/window.h>
#include <state/play_state.h>

Paddle::Paddle(float position_x, float position_y, float width, float height, SDL_Color color, std::string name, float speed, SDL_Texture* texture)
	: MovingEntity(position_x, position_y, width, height, color, name, speed, texture),
	  m_max_influence(1.1f), m_move_scale_factor(.2f){

	m_flag = EntityFlags::FLAG_PADDLE;
	m_collide_mask = EntityFlags::FLAG_BRICK | EntityFlags::FLAG_BALL | EntityFlags::FLAG_POWERUP;

}


void Paddle::Update(const Game& game, const PlayState& state) {
	Entity::Update(game, state);
	Input(game, state);
}

void Paddle::OnHit(Hit hit_result, std::shared_ptr<Entity> other_entity, const std::unique_ptr<EntityFactory>& entity_factory, const Game& game) {
	if (!(other_entity->GetFlag() & FLAG_BALL)) return;
	
	HitAnim(.2f);
}

void Paddle::HitAnim(float duration) {

	m_coroutines->Start([this, m_elapsed = 0.0f, duration](float delta_time) mutable {
		m_elapsed += delta_time;

		if (m_elapsed >= duration) {
			m_render_offset_y = 0;
			return false;
		}

		m_render_offset_y = std::sin(3.1415 * (m_elapsed / duration)) * 20.0f;
		return true;
		});
}

void Paddle::Input(const Game& game, const PlayState& state) {
	m_velocity_x = m_velocity_y = 0;
	
	if (game.m_input_handler->GetKey(SDLK_Q)) {
		m_velocity_x = -m_speed * game.m_input_handler->GetDeltaTime();
	}

	if (game.m_input_handler->GetKey(SDLK_D)) {
		m_velocity_x = m_speed * game.m_input_handler->GetDeltaTime();
	}

	if (m_position_x + m_velocity_x < state.GetSideMargin() + m_width * .5f) m_velocity_x = state.GetSideMargin() + m_width * .5f - m_position_x;
	if (m_position_x + m_velocity_y > game.m_window->GetWidth() - state.GetSideMargin() - m_width * .5f) m_velocity_x = game.m_window->GetWidth() - state.GetSideMargin() - m_width * .5f - m_position_x;

}

void Paddle::Render(const std::unique_ptr<Window>& window) {
	float base_width = m_width;
	float base_height = m_height;
	
	if (m_velocity_x != 0)
	{
		m_width = base_width * (1 + m_move_scale_factor);
		m_height = base_height * (1 - m_move_scale_factor);
	}

	Entity::Render(window);

	m_width = base_width;
	m_height = base_height;
}

void Paddle::ModifyBallDirection(float &dir_x, float &dir_y, const Hit& hit_result) {
	float ratio = std::clamp((m_position_x - hit_result.collision_point.x) / m_width,-.5f,.5f) * 2.0f;
	
	dir_y = -1.0f;
	dir_x = -ratio * m_max_influence;
}