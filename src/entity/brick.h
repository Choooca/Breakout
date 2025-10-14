#pragma once
#include <entity/entity.h>

class Brick : public Entity {
public:

	Brick(float position_x, float position_y, float width, float height, Color color, std::string name, SDL_Texture* texture);

	void Update(const Game& game) override;
	void OnHit(Hit hit_result, std::weak_ptr<Entity> other_entity) override;
};