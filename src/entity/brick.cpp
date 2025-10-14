#include "brick.h"

Brick::Brick(float position_x, float position_y, float width, float height, Color color, std::string name, SDL_Texture* texture)
	: Entity(position_x, position_y, width, height, color, name, texture){ }

void Brick::Update(const Game& game) {}

void Brick::OnHit(Hit hit_result, std::weak_ptr<Entity> other_entity) {
	m_should_be_free = true;
}