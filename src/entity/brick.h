#pragma once
#include <entity/entity.h>

class Brick : public Entity {
public:

	Brick(float position_x, float position_y, float width, float height, Color color);

	void Update(const Game& game) override;
};