#pragma once
#include <entity/entity.h>
#include <entity/moving_entity.h>
#include <utility/aabb_utility.h>

class Ball : public MovingEntity {
public:

	Ball(float position_x, float position_y, float width, float height, Color color, std::string name, float speed);

	void Update(const Game& game) override;
	void OnHit(Hit hit_result, std::weak_ptr<Entity> other_entity) override;

private:

	float m_dir_x;
	float m_dir_y;
};