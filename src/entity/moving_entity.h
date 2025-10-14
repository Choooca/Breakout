#pragma once
#include<entity/entity.h>
#include <SDL3/SDL.h>

class MovingEntity : public Entity {
public:

	MovingEntity(float position_x, float position_y, float width, float height, Color color, std::string name, float speed, SDL_Texture* texture);

	inline float GetXVelocity() { return m_velocity_x; };
	inline float GetYVelocity() { return m_velocity_y; };

protected:

	float m_speed;
	float m_velocity_x, m_velocity_y;
};