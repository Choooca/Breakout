#include "brick.h"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <cmath>

Brick::Brick(float position_x, float position_y, float width, float height, Color color, std::string name, SDL_Texture* texture, bool indestrutible, int health_point)
	: Entity(position_x, position_y, width, height, color, name, texture),
	  m_indestrutible(indestrutible), m_health_point(health_point){ }

void Brick::OnHit(Hit hit_result, std::weak_ptr<Entity> other_entity) {
	
	if (m_indestrutible) return;

	m_health_point -= 1;
	if (m_health_point > 0) {
		HitAnim(.5f);
	}
	else
	{
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
			return false;
		}

		m_render_offset_x = std::rand() % 10 - 5;
		m_render_offset_y = std::rand() % 5 - 2.5f;

		return true;
		});
}

void Brick::DeathAnim(float duration, float max_scale_factor) {
	float base_width = m_width;
	float base_height = m_height;

	m_coroutines->Start([this, m_elapsed = 0.0f, duration, base_width, base_height , max_scale_factor](float delta_time) mutable {
		m_elapsed += delta_time;

		if (m_elapsed >= duration) {
			m_should_be_free = true;
			return false;
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

		return true;
		});
}