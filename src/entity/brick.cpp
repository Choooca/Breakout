#include "brick.h"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <entity/entity_factory.h>
#include <core/game.h>
#include <core/game_event.h>

Brick::Brick(float position_x, float position_y, float width, float height, SDL_Color color, std::string name, SDL_Texture* texture, bool indestrutible, int health_point, int score)
	: Entity(position_x, position_y, width, height, color, name, texture),
	  m_indestrutible(indestrutible), m_health_point(health_point), m_score(score){
	m_flag = EntityFlags::FLAG_BRICK;
	m_collide_mask = EntityFlags::FLAG_BALL | EntityFlags::FLAG_PADDLE;
}

void Brick::OnHit(Hit hit_result, std::shared_ptr<Entity> other_entity) {
	
	if (m_indestrutible) return;



	m_health_point -= 1;
	if (m_health_point > 0) {
		HitAnim(.5f);
		GameEvents::Get().OnHitBrick.Invoke(10);
	}
	else
	{
		GameEvents::Get().OnBrickDestroyed.Invoke(m_score, {m_position_x, m_position_y});
		DeathAnim(.2f);
		m_colliding = false;
	}
}

void Brick::HitAnim(float duration) {
	m_coroutines->Start([this, m_elapsed = 0.0f, duration](float delta_time) mutable {
		m_elapsed += delta_time;
		
		if (m_elapsed >= duration) {
			m_render_offset_x = 0;
			m_render_offset_y = 0;
			return true;
		}

		m_render_offset_x = std::rand() % 10 - 5;
		m_render_offset_y = std::rand() % 5 - 2.5f;

		return false;
		});
}

void Brick::DeathAnim(float duration, float max_scale_factor) {
	float base_width = m_width;
	float base_height = m_height;

	m_coroutines->Start([this, m_elapsed = 0.0f, duration, base_width, base_height , max_scale_factor](float delta_time) mutable {
		m_elapsed += delta_time;

		if (m_elapsed >= duration) {
			m_should_be_free = true;
			return true;
		}

		if (m_elapsed / duration < .2f) {
			m_width = base_width * std::lerp(1, max_scale_factor, m_elapsed / (.1f * duration));
			m_height = base_height * std::lerp(1, max_scale_factor, m_elapsed / (.1f * duration));
		}
		else
		{
			m_width = base_width * std::lerp(max_scale_factor, 0, (m_elapsed - .1f )/ (.9f* duration));
			m_height = base_height * std::lerp(max_scale_factor, 0, (m_elapsed - .1f )/ (.9f * duration));
		}

		return false;
		});
}