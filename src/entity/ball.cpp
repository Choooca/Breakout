#include "ball.h"
#include <algorithm>
#include <iostream>
#include <cmath>
#include <utility/aabb_utility.h>
#include <utility/math_utils.h>
#include <graphics/window.h>
#include <core/game.h>
#include <core/input_handler.h>
#include <state/play_state.h>
#include <cstdlib>

Ball::Ball(float position_x, float position_y, float width, float height, SDL_Color color, std::string name, float speed, SDL_Texture* texture)
	: MovingEntity(position_x, position_y, width, height, color, name, speed, texture),
	  m_dir_x(0),
	  m_dir_y(1) {

	trail_pos.fill({ -100, -100 });

	UpdateTrail();

	float length = std::sqrt(m_dir_x * m_dir_x + m_dir_y * m_dir_y);
	m_dir_x /= length;
	m_dir_y /= length;

	m_flag = EntityFlags::FLAG_BALL;
	m_collide_mask = EntityFlags::FLAG_BRICK | EntityFlags::FLAG_PADDLE;
}

void Ball::UpdateTrail() {
	m_coroutines->Start([this, m_elapsed = 0.0f](float delta_time) mutable {
		m_elapsed += delta_time;
		if (m_elapsed >= .2f) {

			m_elapsed = 0.0f;

			if (trail_pos.size() > 1) {
				for (int i = trail_pos.size() - 1; i > 0; i--) {
					trail_pos[i] = trail_pos[i - 1];
				}
				trail_pos[0] = Vector2(m_position_x, m_position_y);
			}
		}
		return true;
		});
}

void Ball::Update(const Game& game, const PlayState& state) {
	
	Entity::Update(game, state);

	if (std::abs(m_dir_x) < .02f) m_dir_x = .05f;

	if (m_position_y >= game.m_window->GetHeight() - m_height * .5f)
	{
		m_should_be_free = true;
	}

	m_velocity_x = m_velocity_y = 0;

	m_velocity_x = game.m_input_handler->GetDeltaTime() * m_speed * m_dir_x;
	m_velocity_y = game.m_input_handler->GetDeltaTime() * m_speed * m_dir_y;
}

void Ball::Render(const std::unique_ptr<Window>& window) {
	Entity::Render(window);

	for (int i = 0; i < trail_pos.size(); i++) {

		float factor = std::lerp(1.0f, 0.0f, (i + 1.0f) / (trail_pos.size() + 1));
		float alpha = m_color.a * factor;
		float width = m_width * factor;
		float height = m_height * factor;

		if (!m_texture) {
			SDL_SetRenderDrawColor(window->GetRenderer(), m_color.r, m_color.g, m_color.b, m_color.a);
			SDL_FRect paddle_rect = { trail_pos[i].x - width * .5f,  trail_pos[i].y - height * .5f, width, height };
			SDL_RenderFillRect(window->GetRenderer(), &paddle_rect);
			return;
		}

		SDL_SetTextureAlphaMod(m_texture, alpha);
		SDL_SetTextureColorMod(m_texture, m_color.r, m_color.g, m_color.b);
		SDL_FRect rect = { trail_pos[i].x - width * .5f + m_render_offset_x, trail_pos[i].y - height * .5f + m_render_offset_y, width, height };
		SDL_RenderTexture(window->GetRenderer(), m_texture, nullptr, &rect);

	}
}

void Ball::OnHit(Hit hit_result, std::shared_ptr<Entity> other_entity, const std::unique_ptr<EntityFactory>& entity_factory, const Game& game) {

	m_velocity_x *= hit_result.collision_time;
	m_velocity_y *= hit_result.collision_time;
	other_entity->ModifyBallDirection(m_dir_x, m_dir_y, hit_result);

	NormalizeDir();
	
}

void Ball::SetRandomDir() {
	m_dir_x =  (rand() % 10) - 5;
	m_dir_y = - rand() % 5 - 1;

	NormalizeDir();
}

void Ball::NormalizeDir() {
	float length = std::sqrt(m_dir_x * m_dir_x + m_dir_y * m_dir_y);
	m_dir_x /= length;
	m_dir_y /= length;
}

