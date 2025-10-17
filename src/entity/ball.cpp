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

Ball::Ball(Vector2 position, Vector2 size, SDL_Color color, std::string name, float speed, SDL_Texture* texture)
	: MovingEntity(position, size, color, name, speed, texture),
	  m_dir_x(0),
	  m_dir_y(0) {

	trail_pos.fill({ -100, -100 });

	UpdateTrail();

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
				trail_pos[0] = Vector2(m_position.x, m_position.y);
			}
		}
		return false;
		});
}

void Ball::Update(const std::unique_ptr<InputHandler>& input_handler, int window_height) {
	
	Entity::Update(input_handler, window_height);

	if (std::sqrt(m_dir_x * m_dir_x + m_dir_y * m_dir_y) == 0) return;

	if (std::abs(m_dir_x) < .01f) m_dir_x = .01f;

	if (m_position.y >= window_height - m_size.y * .5f)
	{
		m_should_be_free = true;
	}

	m_velocity = { 0 };

	m_velocity.x = input_handler->GetDeltaTime() * m_speed * m_dir_x;
	m_velocity.y = input_handler->GetDeltaTime() * m_speed * m_dir_y;
}

void Ball::Render(const std::unique_ptr<Window>& window) {
	Entity::Render(window);

	for (int i = 0; i < trail_pos.size(); i++) {

		float factor = std::lerp(1.0f, 0.0f, (i + 1.0f) / (trail_pos.size() + 1));
		float alpha = m_color.a * factor;
		Vector2 size = { m_size.x * factor, m_size.y * factor };

		if (!m_texture) {
			SDL_SetRenderDrawColor(window->GetRenderer(), m_color.r, m_color.g, m_color.b, m_color.a);
			SDL_FRect paddle_rect = { trail_pos[i].x - size.x * .5f,  trail_pos[i].y - size.y * .5f, size.x, size.y };
			SDL_RenderFillRect(window->GetRenderer(), &paddle_rect);
			return;
		}

		SDL_SetTextureAlphaMod(m_texture, alpha);
		SDL_SetTextureColorMod(m_texture, m_color.r, m_color.g, m_color.b);
		SDL_FRect rect = { trail_pos[i].x - size.x * .5f + m_render_offset.x, trail_pos[i].y - size.y * .5f + m_render_offset.y, size.x, size.y};
		SDL_RenderTexture(window->GetRenderer(), m_texture, nullptr, &rect);

	}
}

void Ball::OnHit(Hit hit_result, std::shared_ptr<Entity> other_entity) {
	
	if(!(other_entity->GetFlag() & FLAG_PADDLE)) MovingEntity::OnHit(hit_result, other_entity);

	other_entity->ModifyBallDirection(m_dir_x, m_dir_y, hit_result);

	NormalizeDir();
	
}

void Ball::SetRandomDir() {
	m_dir_x =  (rand() % 10) - 5;
	m_dir_y = - rand() % 5 - 1;

	NormalizeDir();
}

void Ball::SetDir(Vector2 dir) {
	m_dir_x = dir.x;
	m_dir_y = dir.y;
}

void Ball::NormalizeDir() {
	float length = std::sqrt(m_dir_x * m_dir_x + m_dir_y * m_dir_y);
	if (length == 0) return;
	m_dir_x /= length;
	m_dir_y /= length;
}

