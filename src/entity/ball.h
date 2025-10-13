#pragma once
#include <entity/entity.h>
#include <entity/moving_entity.h>
#include <utility/aabb_utility.h>

class Ball : public MovingEntity {
public:

	Ball(float position_x, float position_y, float width, float height, Color color, float speed);

	void Update(const Game& game) override;
	void OnHit(Hit hit_result) override;

private:

	float m_dir_x;
	float m_dir_y;
};