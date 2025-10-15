#pragma once
#include <entity/moving_entity.h>

class PowerUp : public MovingEntity {
public:
	PowerUp(float position_x, float position_y, float width, float height, Color color, std::string name, float speed, SDL_Texture* texture);

	void Update(const Game& game, const PlayState& state) override;

	void OnHit(Hit hit_result, std::shared_ptr<Entity> other_entity, const std::unique_ptr<EntityFactory>& entity_factory, const Game& game) override;
};