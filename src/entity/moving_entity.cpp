#include "moving_entity.h"

MovingEntity::MovingEntity(float position_x, float position_y, float width, float height, SDL_Color color, std::string name, float speed, SDL_Texture* texture) :
	Entity(position_x, position_y, width, height, color, name, texture),
	m_speed(speed),
	m_velocity_x(0),
	m_velocity_y(0){}


void MovingEntity::OnHit(Hit hit_result, std::shared_ptr<Entity> other_entity) {
	m_velocity_x *= hit_result.collision_time;
	m_velocity_y *= hit_result.collision_time;
}