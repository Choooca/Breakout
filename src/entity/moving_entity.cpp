#include "moving_entity.h"

MovingEntity::MovingEntity(float position_x, float position_y, float width, float height, Color color, float speed) :
	Entity(position_x, position_y, width, height, color),
	m_speed(speed){}
