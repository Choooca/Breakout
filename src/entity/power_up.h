#pragma once
#include <entity/moving_entity.h>
#include <entity/entity.h>

class PowerUp : public MovingEntity {
public:
	PowerUp(float position_x, float position_y, float width, float height, SDL_Color color, std::string name, float speed, SDL_Texture* texture);

	void Update(const std::unique_ptr<InputHandler>& input_handler, int window_height) override;

	void OnHit(Hit hit_result, std::shared_ptr<Entity> other_entity) override;
};