#include "brick.h"

Brick::Brick(float position_x, float position_y, float width, float height, Color color)
	: Entity(position_x, position_y, width, height, color){ }

void Brick::Update(const Game& game) {}