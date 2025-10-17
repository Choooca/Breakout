#include "brick.h"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <entity/entity_factory.h>
#include <core/game.h>
#include <core/game_event.h>
#include <utility/math_utils.h>

Brick::Brick(Vector2 position, Vector2 size, SDL_Color color, std::string name, SDL_Texture* texture, bool indestrutible, int health_point, int score) :
	Entity(position, size, color, name, texture),
	m_indestrutible(indestrutible),
	m_health_point(health_point), m_score(score){
	m_flag = EntityFlags::FLAG_BRICK;
	m_collide_mask = EntityFlags::FLAG_BALL | EntityFlags::FLAG_PADDLE;
	m_base_health_point = health_point;
}

void Brick::OnHit(Hit hit_result, std::shared_ptr<Entity> other_entity) {
	
	if (m_indestrutible) return;

	m_health_point -= 1;
	if (m_health_point > 0) {
		unsigned char gb = std::lerp(0.0f, 255.0f, static_cast<float>(m_health_point) / static_cast<float>(m_base_health_point));
		m_color = { 255,gb,gb,255};
		HitAnim(.5f);
		GameEvents::Get().OnHitBrick.Invoke(10);
	}
	else
	{
		GameEvents::Get().OnBrickDestroyed.Invoke(m_score, m_position);
		DeathAnim(.2f);
		m_colliding = false;
	}
}

void Brick::HitAnim(float duration) {
	m_coroutines->Start([this, m_elapsed = 0.0f, duration](float delta_time) mutable {
		m_elapsed += delta_time;
		
		if (m_elapsed >= duration) {
			m_render_offset.x = 0;
			m_render_offset.y = 0;
			return true;
		}

		m_render_offset.x = std::rand() % 10 - 5;
		m_render_offset.y = std::rand() % 5 - 2.5f;

		return false;
		});
}

void Brick::DeathAnim(float duration, float max_scale_factor) {
	Vector2 base_size = m_size;

	m_coroutines->Start([this, m_elapsed = 0.0f, duration, base_size , max_scale_factor](float delta_time) mutable {
		m_elapsed += delta_time;

		if (m_elapsed >= duration) {
			m_should_be_free = true;
			return true;
		}

		if (m_elapsed / duration < .2f) {
			m_size.x = base_size.x * std::lerp(1, max_scale_factor, m_elapsed / (.1f * duration));
			m_size.y = base_size.y * std::lerp(1, max_scale_factor, m_elapsed / (.1f * duration));
		}
		else
		{
			m_size.x = base_size.x * std::lerp(max_scale_factor, 0, (m_elapsed - .1f )/ (.9f* duration));
			m_size.y = base_size.y * std::lerp(max_scale_factor, 0, (m_elapsed - .1f )/ (.9f * duration));
		}

		return false;
		});
}