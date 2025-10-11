#include <entity/entity.h>

Entity::Entity(float position_x, float position_y, float width, float height)
	: m_position_x(position_x),
	  m_position_y(position_y),
	  m_width(width),
	  m_height(height) {}