#pragma once
#include <entity/entity.h>

class MovingEntity : public Entity {
public:

	MovingEntity(float position_x, float position_y, float width, float height, Color color, float speed);

	inline float GetXVelocity() { return m_velocity_x; };
	inline float GetYVelocity() { return m_velocity_y; };

protected:

	float m_speed;
	float m_velocity_x, m_velocity_y;
};