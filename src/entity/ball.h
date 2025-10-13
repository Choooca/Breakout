#pragma once
#include <entity/entity.h>

class Ball : public Entity {
public:

	Ball(float position_x, float position_y, float width, float height, Color color);

	void Update(const Game& game) override;
private:

	float m_speed;

	float m_dir_x;
	float m_dir_y;
};