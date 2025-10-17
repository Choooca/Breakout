#include "moving_entity.h"

MovingEntity::MovingEntity(Vector2 position, Vector2 size, SDL_Color color, std::string name, float speed, SDL_Texture* texture) :
	Entity(position, size, color, name, texture),
	m_speed(speed),
	m_velocity(0){}


void MovingEntity::OnHit(Hit hit_result, std::shared_ptr<Entity> other_entity) {
	m_velocity.x *= hit_result.collision_time;
	m_velocity.y *= hit_result.collision_time;
}

void MovingEntity::SetUpdateEnable(bool is_enable) {
	Entity::SetUpdateEnable(is_enable);

	if (!is_enable) {
		m_velocity = { 0 };
	}
}
