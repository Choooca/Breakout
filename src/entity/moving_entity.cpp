#include "moving_entity.h"

MovingEntity::MovingEntity(float position_x, float position_y, float width, float height, Color color, std::string name, float speed) :
	Entity(position_x, position_y, width, height, color, name),
	m_speed(speed){}
